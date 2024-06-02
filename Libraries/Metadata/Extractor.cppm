/**
 * @file    Extractor.cppm
 * @author  Oleg E. Vorobiov <isnullxbh(at)gmail.com>
 * @date    01.06.2024
 */

module;

#include <filesystem>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#   include <clang/ASTMatchers/ASTMatchFinder.h>
#   include <clang/ASTMatchers/ASTMatchers.h>
#   include <clang/Basic/Diagnostic.h>
#   include <clang/Frontend/ASTUnit.h>
#   include <clang/Frontend/CompilerInstance.h>
#   include <clang/Serialization/PCHContainerOperations.h>
#pragma clang diagnostic pop

export module Morpheus.Metadata.Extractor;

export import Morpheus.Metadata.EntityRegistry;

import Std.Algorithms;
import Std.Vector;
import Std.Strings;
import Morpheus.Metadata.Class;
import Morpheus.Metadata.HasEntityAttribute;

namespace Morpheus::Metadata
{

template<typename Declaration, typename Entity>
class Callback : public clang::ast_matchers::MatchFinder::MatchCallback
{
public:
    explicit Callback(std::string_view id, EntityRegistry& registry)
        : _id(id)
        , _registry(&registry)
    {}

    void run(const clang::ast_matchers::MatchFinder::MatchResult& result) final
    {
        if (const auto* declaration = result.Nodes.getNodeAs<Declaration>(_id))
        {
            if (result.Context->getSourceManager().isWrittenInMainFile(declaration->getLocation()))
            {
                _registry->add(Entity::extract(declaration));
            }
        }
    }

private:
    std::string     _id;
    EntityRegistry* _registry;
};

export class Extractor
{
public:
    struct Options
    {};

    Extractor()
        : _diagnostic_options()
        , _diagnostic_engine(clang::CompilerInstance::createDiagnostics(new clang::DiagnosticOptions()))
        , _registry(std::make_shared<clang::PCHContainerOperations>())
    {
    }

    Extractor(const Extractor&) = delete;
    Extractor(Extractor&&) = delete;

    auto operator=(const Extractor&) -> Extractor& = delete;
    auto operator=(Extractor&&) -> Extractor& = delete;

    auto extract(const std::filesystem::path& path, const Options& options) -> EntityRegistry
    {
        _diagnostic_engine->Clear();

        std::vector<std::string> args {};
        args.emplace_back("<service>");
        // TODO: retrieve include path from compiler
        args.push_back("-I/usr/local/opt/llvm/bin/../include/c++/v1");
        args.push_back("-I/usr/local/Cellar/llvm/18.1.5/lib/clang/18/include");
        args.push_back("-I/Library/Developer/CommandLineTools/SDKs/MacOSX14.sdk/usr/include");
        args.push_back("-I/Library/Developer/CommandLineTools/SDKs/MacOSX14.sdk/System/Library/Frameworks");
        args.push_back("-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk/usr/include");
        args.push_back(path.generic_string());

        std::vector<const char*> args_view {};
        std::transform(args.cbegin(), args.cend(), std::back_inserter(args_view),
            [](const std::string& s){ return s.data(); });

        std::unique_ptr<clang::ASTUnit> unit {
            clang::ASTUnit::LoadFromCommandLine(args_view.data(), args_view.data() + args_view.size(), _registry,
                _diagnostic_engine, llvm::StringRef()) };

        if (!unit || _diagnostic_engine->getNumErrors() > 0)
        {
            throw 1;
        }

        EntityRegistry registry;

        clang::ast_matchers::MatchFinder finder;
        Callback<clang::CXXRecordDecl, Class> callback { "class", registry };

        finder.addMatcher(
            clang::ast_matchers::cxxRecordDecl(
                clang::ast_matchers::unless(clang::ast_matchers::isImplicit()),
                hasEntityAttribute()).bind("class"),
            &callback);

        finder.matchAST(unit->getASTContext());

        return registry;
    }

private:
    clang::DiagnosticOptions                            _diagnostic_options;
    clang::IntrusiveRefCntPtr<clang::DiagnosticsEngine> _diagnostic_engine;
    std::shared_ptr<clang::PCHContainerOperations>      _registry;
};

} // namespace Morpheus::Metadata
