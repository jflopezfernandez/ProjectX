
#ifndef PROJECT_X_INCLUDES_PROGRAMMING_LANGUAGES_HPP_
#define PROJECT_X_INCLUDES_PROGRAMMING_LANGUAGES_HPP_

enum class ProgrammingLanguage {
    Text,
    C,
    Cpp,
    Perl,
    Python,
    CommonLisp,
    Haskell
};

const auto None       = ProgrammingLanguage::Text;
const auto Text       = ProgrammingLanguage::Text;
const auto C          = ProgrammingLanguage::C;
const auto Cpp        = ProgrammingLanguage::Cpp;
const auto Perl       = ProgrammingLanguage::Perl;
const auto Python     = ProgrammingLanguage::Python;
const auto CommonLisp = ProgrammingLanguage::CommonLisp;
const auto Haskell    = ProgrammingLanguage::Haskell;

std::ostream& operator<<(std::ostream& outputStream, ProgrammingLanguage lang)
{
    const auto langToStr = [=](ProgrammingLanguage lang)
    {
        switch (lang)
        {
            case ProgrammingLanguage::C: {
                return "C";
            }

            case ProgrammingLanguage::Cpp: {
                return "C++";
            }

            case ProgrammingLanguage::Perl: {
                return "Perl";
            }

            case ProgrammingLanguage::Python: {
                return "Python";
            }

            case ProgrammingLanguage::CommonLisp: {
                return "Common Lisp";
            }

            case ProgrammingLanguage::Haskell: {
                return "Haskell";
            }

            default: {
                return "Plain Text";
            }
        }
    }(lang);

    return outputStream << langToStr;
}

using LanguageExtensionMap     = std::map<ProgrammingLanguage, FileExtension>;
using LanguageExtensionMapIter = std::map<ProgrammingLanguage, FileExtension>::iterator;

#endif // PROJECT_X_INCLUDES_PROGRAMMING_LANGUAGES_HPP_
