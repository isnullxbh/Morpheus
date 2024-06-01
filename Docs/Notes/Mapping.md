# Mappings

C++ code like this:

**UDF + attributes**

```c++
[[clang::annotate("Morpheus::Entity", "USERS")]]
struct User
{
    [[clang::annotate("Morpheus::Column", "ID")]]
    int id;

    [[clang::annotate("Morpheus::Column", "FN")]]
    std::string name;

    [[clang::annotate("Morpheus::Column", "SN")]]
    std::string surname;
};
```

translates to the following:

**mappings**

```c++
template<>
struct Entity<User>
{
    static constexpr std::string_view table { "USERS" };

    static constexpr Column<&User::id>      id      { "ID" };
    static constexpr Column<&User::name>    name    { "FN" };
    static constexpr Column<&User::surname> surname { "SN" };

    template<typename F>
    static constexpr auto for_each(F&& f) -> void
    {
        (f(mappings), ...);
        // Where mappings is arg pack formed from mappings
    }
};
```
