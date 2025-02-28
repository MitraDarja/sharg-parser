#include <sharg/all.hpp>

int main(int argc, const char ** argv)
{
    sharg::parser myparser{"Test", argc, argv}; // initialize

    //! [validator_call]
    std::filesystem::path myfile{};

    // Use the sharg::output_file_open_options to indicate that you allow overwriting existing output files, ...
    myparser.add_option(myfile, 'f', "file", "Output file containing the processed sequences.",
                        sharg::option_spec::standard,
                        sharg::output_file_validator{sharg::output_file_open_options::open_or_create, {"fa","fasta"}});

    // ... or that you will throw a sharg::validation_error if the user specified output file already exists
    // No sharg::output_file_open_options is passed: The default sharg::output_file_open_options::create_new is used.
    // Possible extensions can also be passed as separate arguments.
    myparser.add_option(myfile, 'g', "file2", "Output file containing the processed sequences.",
                        sharg::option_spec::standard,
                        sharg::output_file_validator{"fa","fasta"});
    //! [validator_call]

    // an exception will be thrown if the user specifies a filename
    // that does not have one of the extensions ["fa","fasta"],
    // if the file already exists, or if the file is not writable.
    try
    {
        myparser.parse();
    }
    catch (sharg::parser_error const & ext) // the user did something wrong
    {
        std::cerr << "[PARSER ERROR] " << ext.what() << "\n"; // customize your error message
        return -1;
    }

    std::cerr << "filename given by user passed validation: " << myfile << "\n";
    return 0;
}
