#include "form.h"

#include <set>

namespace {
std::set<char> unique_yess(std::vector<std::string> const &answers) {
  std::set<char> yess;
  for (auto const &answer : answers) {
    for (auto const yes : answer) {
      yess.insert(yes);
    }
  }
  return yess;
}

} // namespace

uint any_yes(std::vector<std::string> const &answers) {
  auto yess = unique_yess(answers);
  return yess.size();
}

uint all_yes(std::vector<std::string> const &answers) {
  auto yess = unique_yess(answers);
  return std::count_if(yess.begin(), yess.end(), [&](auto yes) {
    return std::all_of(answers.begin(), answers.end(), [&](auto answer) {
      return answer.find(yes) != std::string::npos;
    });
  });
}
