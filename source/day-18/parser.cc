#include "parser.h"

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace new_math {

x3::rule<class expression, uint64_t> const expression = "expression";
x3::rule<class term, uint64_t> const term = "term";

auto const set = [](auto &context) { x3::_val(context) = x3::_attr(context); };
auto const add = [](auto &context) { x3::_val(context) += x3::_attr(context); };
auto const mul = [](auto &context) { x3::_val(context) *= x3::_attr(context); };

auto const expression_def = term[set] >>
                            *(('+' >> term[add]) | ('*' >> term[mul]));
auto const term_def = x3::uint_ | ('(' >> expression >> ')');

BOOST_SPIRIT_DEFINE(expression, term);

} // namespace new_math

namespace advanced_math {

auto const set = [](auto &context) { x3::_val(context) = x3::_attr(context); };
auto const add = [](auto &context) { x3::_val(context) += x3::_attr(context); };
auto const mul = [](auto &context) { x3::_val(context) *= x3::_attr(context); };

x3::rule<class expression, uint64_t> const expression = "expression";
x3::rule<class term, uint64_t> const term = "term";
x3::rule<class factor, uint64_t> const factor = "factor";

auto const expression_def = factor[set] >> *('*' >> factor[mul]);
auto const factor_def = term[set] >> *('+' >> term[add]);
auto const term_def = x3::uint_ | ('(' >> expression >> ')');

BOOST_SPIRIT_DEFINE(expression, term, factor);

} // namespace advanced_math

uint64_t parse_expression(std::string input, Math math) {
  uint64_t result = 0;

  auto first = input.begin();
  auto last = input.end();

  auto passed = math == Math::New
                    ? x3::phrase_parse(first, last, new_math::expression,
                                       x3::space, result)
                    : x3::phrase_parse(first, last, advanced_math::expression,
                                       x3::space, result);

  if (not passed || first != last) {
    throw std::invalid_argument{"parse error"};
  }

  return result;
}
