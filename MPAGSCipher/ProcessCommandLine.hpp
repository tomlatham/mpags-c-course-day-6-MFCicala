#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

// Standard library includes
#include <string>
#include <vector>

// Our project headers
#include "CipherMode.hpp"
#include "CipherType.hpp"

/**
 * \file ProcessCommandLine.hpp
 * \brief Contains the declarations of the data structures and functions associated with the processing of command-line arguments including exceptions
 */


/**
 * \class MissingArgument
 * \brief Exception object to indicate the case of missing arguments from command line
 */

class MissingArgument : public std::invalid_argument {
public:
  /**
   * \brief Construct a MissingArgument exception
   * \param msg the diagnostic message
   */
  MissingArgument( const std::string& msg):
    std::invalid_argument(msg){}
};


/**
 * \class UnknownArgument
 * \brief Exception object to indicate the case of unknown arguments from command line
 */

class UnknownArgument : public std::invalid_argument {
public:
  /**
   * \brief Construct a UnknownArgument exception
   * \param msg the diagnostic message
   */
  UnknownArgument( const std::string& msg):
    std::invalid_argument(msg){}
};


/**
 * \struct ProgramSettings
 * \brief Holds the settings of the program that can be modified by command-line arguments
 */
struct ProgramSettings {
  bool helpRequested;     ///< Indicates the presence of the help flag in the arguments
  bool versionRequested;  ///< Indicates the presence of the version flag in the arguments
  std::string inputFile;  ///< Name of the input file
  std::string outputFile; ///< Name of the output file
  std::string cipherKey;  ///< Key to be used in encrypting/decrypting routine
  CipherMode cipherMode;  ///< Flag indicating the mode in which the cipher should run (i.e. encrypt or decrypt)
  CipherType cipherType;  ///< Flag to indicate which cipher to use (e.g. Caesar, Playfair, etc.)
};

/**
 * \brief Processes the command-line arguments and modifies accordingly the program settings
 *
 * \param args the command-line arguments to be processed
 * \param settings the program settings to be modified based upon the arguments received
 *
 * \exception MissingArgument will be emitted if an expected argument is not found during parsing
 * \exception UnknownArgument will be emitted if an argument encountered during parsing is not recognised
 */
void processCommandLine(const std::vector<std::string>& args, ProgramSettings& settings);

#endif // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP 
