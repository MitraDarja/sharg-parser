#include <sharg/all.hpp>

namespace foo
{

enum class bar
{
    one,
    two,
    three
};

// Specialise a mapping from an identifying string to the respective value of your type bar.
auto enumeration_names(bar)
{
    return std::unordered_map<std::string_view, bar>{{"one", bar::one}, {"two", bar::two}, {"three", bar::three}};
}

} // namespace foo

int main(int argc, char const * argv[])
{
    foo::bar value{};

    sharg::parser parser{"my_program", argc, argv};

    // Because of the enumeration_names function
    // you can now add an option that takes a value of type bar:
    parser.add_option(value, 'f', "foo", "Give me a foo value.", sharg::option_spec::standard,
                      sharg::value_list_validator{(sharg::enumeration_names<foo::bar> | std::views::values)});

    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext) // the user did something wrong
    {
        std::cerr << "[PARSER ERROR] " << ext.what() << "\n"; // customize your error message
        return -1;
    }
}
