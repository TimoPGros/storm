#pragma once

#include "storm/parser/SpiritParserDefinitions.h"

#include "storm/utility/macros.h"
#include "storm/exceptions/WrongFormatException.h"

namespace storm {
    namespace parser {
        // Functor used for displaying error information.
        struct SpiritErrorHandler {
            typedef qi::error_handler_result result_type;
            
            template<typename T1, typename T2, typename T3, typename T4>
            qi::error_handler_result operator()(T1 b, T2 e, T3 where, T4 const& what) const {
                auto lineStart = boost::spirit::get_line_start(b, where);
                auto lineEnd = std::find(where, e, '\n');
                std::string line(lineStart, lineEnd);
                
                std::stringstream stream;
                stream << "Parsing error at " << get_line(where) << ":" << boost::spirit::get_column(lineStart, where) << ": " << " expecting " << what << ", here:" << std::endl;
                stream << "\t" << line << std::endl;
                auto caretColumn = boost::spirit::get_column(lineStart, where);
                stream << "\t" << std::string(caretColumn - 1, ' ') << "^" << std::endl;
                
                STORM_LOG_THROW(false, storm::exceptions::WrongFormatException, stream.str());
                return qi::fail;
            }
        };
    }
}
