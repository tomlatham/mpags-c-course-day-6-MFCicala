
// Standard library includes
#include <string>
#include <vector>

// Out project headers
#include "Alphabet.hpp"
#include "CaesarCipher.hpp"

CaesarCipher::CaesarCipher( const size_t key )
  : key_{key%Alphabet::size}
{
}


CaesarCipher::CaesarCipher( const std::string& key )
  : key_{0}
{
  // We have the key as a string, but the Caesar cipher needs an unsigned long, so we first need to convert it
  // We default to having a key of 0, i.e. no encryption, if no (valid) key was provided on the command line

  if ( ! key.empty() ) {

    // First, explicitly check for negative numbers - these will convert successfully but will not lead to expected results
    if ( key.front() == '-' ) {
      throw InvalidKey("Caesar cipher key must be an unsigned long integer, the supplied key (" + key + ") could not be successfully converted");
    }

    try{
    key_ = std::stoul(key) % Alphabet::size;
    } catch(std::invalid_argument& e){
      throw InvalidKey("Caesar cipher key must be an unsigned long integer for Caesar cipher, the supplied key (" + key + ") could not be successfully converted");
    } catch(std::out_of_range& e){
      throw InvalidKey("Caesar cipher key must be an unsigned long integer for Caesar cipher, the supplied key (" + key + ") is too big and could not be successfully converted");
    }
  }
}



std::string CaesarCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  // Create the output string
  std::string outputText {};

  // Loop over the input text
  char processedChar {'x'};
  for ( const auto& origChar : inputText ) {

    // For each character in the input text, find the corresponding position in
    // the alphabet by using an indexed loop over the alphabet container
    for ( Alphabet::AlphabetSize i{0}; i < Alphabet::size; ++i ) {

      if ( origChar == Alphabet::alphabet[i] ) {

	// Apply the appropriate shift (depending on whether we're encrypting
	// or decrypting) and determine the new character
	// Can then break out of the loop over the alphabet
	switch ( cipherMode ) {
	  case CipherMode::Encrypt :
	    processedChar = Alphabet::alphabet[ (i + key_) % Alphabet::size ];
	    break;
	  case CipherMode::Decrypt :
	    processedChar = Alphabet::alphabet[ (i + Alphabet::size - key_) % Alphabet::size ];
	    break;
	}
	break;
      }
    }

    // Add the new character to the output text
    outputText += processedChar;
  }

  return outputText;
}
