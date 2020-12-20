#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "message.h"

std::string const example{
    R"(0: 14 16
11: 12 13 | 13 12
12: 14 14 | 15 15
13: 14 15 | 15 14
14: "a"
15: "b"
16: 11 15

ababbb
bababa
abbbab
aaabbb
aaaabbb
)"};

TEST_CASE("Parse Input") {
  std::istringstream input{example};
  auto [language, messages] = parse_input(input);

  REQUIRE(language.size() == 7);

  REQUIRE(messages.size() == 5);
  REQUIRE(messages[1] == "bababa");
  REQUIRE(messages[2] == "abbbab");
}

TEST_CASE("Parse terminal rule") {
  auto const rule = parse_rule(R"(7: "x")");
  REQUIRE(rule.first == 7);
  REQUIRE(rule.second.size() == 1);
  REQUIRE(std::holds_alternative<Terminal>(rule.second[0]));
  REQUIRE(std::get<Terminal>(rule.second[0]) == 'x');
}

TEST_CASE("Parse variable rule") {
  auto const rule = parse_rule(R"(23: 14 13)");
  REQUIRE(rule.first == 23);
  REQUIRE(rule.second.size() == 1);
  REQUIRE(std::holds_alternative<Variables>(rule.second[0]));
  REQUIRE(std::get<Variables>(rule.second[0]).first == 14);
  REQUIRE(std::get<Variables>(rule.second[0]).second == 13);
}

TEST_CASE("Parse multiple rules") {
  auto const rule = parse_rule(R"(12: 1 11 | 24 33)");
  REQUIRE(rule.first == 12);
  REQUIRE(rule.second.size() == 2);

  REQUIRE(std::holds_alternative<Variables>(rule.second[0]));
  REQUIRE(std::holds_alternative<Variables>(rule.second[1]));
  REQUIRE(std::get<Variables>(rule.second[0]).second == 11);
  REQUIRE(std::get<Variables>(rule.second[1]).first == 24);
}

TEST_CASE("Parse non-normal rule") {
  auto const rule = parse_rule(R"(8: 42)");
  REQUIRE(rule.first == 8);
  REQUIRE(rule.second.size() == 1);

  REQUIRE(std::holds_alternative<Singular>(rule.second[0]));
  REQUIRE(std::get<Singular>(rule.second[0]) == 42);
}

TEST_CASE("Parse non-normal rule with or") {
  auto const rule = parse_rule(R"(33: 121 | 96)");
  REQUIRE(rule.first == 33);
  REQUIRE(rule.second.size() == 2);

  REQUIRE(std::holds_alternative<Singular>(rule.second[0]));
  REQUIRE(std::holds_alternative<Singular>(rule.second[1]));
  REQUIRE(std::get<Singular>(rule.second[0]) == 121);
  REQUIRE(std::get<Singular>(rule.second[1]) == 96);
}

TEST_CASE("Normalize to terminal") {
  std::istringstream input{R"(1: 23
23: "a"
)"};
  auto [language, messages] = parse_input(input);
  language = normalize(language);

  REQUIRE(language.size() == 2);
  REQUIRE(language.contains(1));
  REQUIRE(language.at(1).size() == 1);
  REQUIRE(std::holds_alternative<Terminal>(language.at(1)[0]));
  REQUIRE(std::get<Terminal>(language.at(1)[0]) == 'a');

  REQUIRE(language.contains(23));
  REQUIRE(language.at(23).size() == 1);
  REQUIRE(std::holds_alternative<Terminal>(language.at(23)[0]));
  REQUIRE(std::get<Terminal>(language.at(23)[0]) == 'a');
}

TEST_CASE("Normalize to multiple terminals") {
  std::istringstream input{R"(42: 23 | 17
23: "a"
17: "z"
)"};
  auto [language, messages] = parse_input(input);
  language = normalize(language);

  REQUIRE(language.size() == 3);

  REQUIRE(language.contains(42));

  REQUIRE(language.at(42).size() == 2);
  REQUIRE(std::holds_alternative<Terminal>(language.at(42)[0]));
  REQUIRE(std::get<Terminal>(language.at(42)[0]) == 'a');

  REQUIRE(std::holds_alternative<Terminal>(language.at(42)[1]));
  REQUIRE(std::get<Terminal>(language.at(42)[1]) == 'z');
}

TEST_CASE("Normalize to variables") {
  std::istringstream input{R"(15: 17
17: 22 33
)"};
  auto [language, messages] = parse_input(input);
  language = normalize(language);

  REQUIRE(language.size() == 2);
  REQUIRE(language.contains(15));
  REQUIRE(language.at(15).size() == 1);
  REQUIRE(std::holds_alternative<Variables>(language.at(15)[0]));
  REQUIRE(std::get<Variables>(language.at(15)[0]).first == 22);
  REQUIRE(std::get<Variables>(language.at(15)[0]).second == 33);
}

TEST_CASE("Normalize to multiple variables") {
  std::istringstream input{R"(66: 2 | 3
2: 77 78
3: 88 98
)"};
  auto [language, messages] = parse_input(input);
  language = normalize(language);

  REQUIRE(language.size() == 3);

  REQUIRE(language.contains(2));
  REQUIRE(language.at(2).size() == 1);
  REQUIRE(std::holds_alternative<Variables>(language.at(2)[0]));
  REQUIRE(std::get<Variables>(language.at(2)[0]).first == 77);
  REQUIRE(std::get<Variables>(language.at(2)[0]).second == 78);

  REQUIRE(language.contains(3));
  REQUIRE(language.at(3).size() == 1);
  REQUIRE(std::holds_alternative<Variables>(language.at(3)[0]));
  REQUIRE(std::get<Variables>(language.at(3)[0]).first == 88);
  REQUIRE(std::get<Variables>(language.at(3)[0]).second == 98);
}

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto [language, messages] = parse_input(input);
  language = normalize(language);

  REQUIRE(is_valid(language, messages[0]));
  REQUIRE(is_valid(language, messages[2]));

  REQUIRE(not is_valid(language, messages[1]));
  REQUIRE(not is_valid(language, messages[3]));
  REQUIRE(not is_valid(language, messages[4]));

  REQUIRE(count_valid(language, messages) == 2);
}

std::string const example2{R"(42: 9 14 | 10 1
9: 14 27 | 1 26
10: 23 14 | 28 1
1: "a"
11: 42 31
5: 1 14 | 15 1
19: 14 1 | 14 14
12: 24 14 | 19 1
16: 15 1 | 14 14
31: 14 17 | 1 13
6: 14 14 | 1 14
2: 1 24 | 14 4
0: 8 11
13: 14 3 | 1 12
15: 1 | 14
17: 14 2 | 1 7
23: 25 1 | 22 14
28: 16 1
4: 1 1
20: 14 14 | 1 15
3: 5 14 | 16 1
27: 1 6 | 14 18
14: "b"
21: 14 1 | 1 14
25: 1 1 | 1 14
22: 14 14
8: 42
26: 14 22 | 1 20
18: 15 15
7: 14 5 | 1 21
24: 14 1

abbbbbabbbaaaababbaabbbbabababbbabbbbbbabaaaa
bbabbbbaabaabba
babbbbaabbbbbabbbbbbaabaaabaaa
aaabbbbbbaaaabaababaabababbabaaabbababababaaa
bbbbbbbaaaabbbbaaabbabaaa
bbbababbbbaaaaaaaabbababaaababaabab
ababaaaaaabaaab
ababaaaaabbbaba
baabbaaaabbaaaababbaababb
abbbbabbbbaaaababbbbbbaaaababb
aaaaabbaabaaaaababaa
aaaabbaaaabbaaa
aaaabbaabbaaaaaaabbbabbbaaabbaabaaa
babaaabbbaaabaababbaabababaaab
aabbbbbaabbbaaaaaabbbbbababaaaaabbaaabba
)"};

TEST_CASE("Patch rules") {
  std::istringstream input{example2};
  auto const [language, messages] = parse_input(input);

  // 8: 42 | 42 8
  // 11: 42 31 | 42 11 31
  auto const fixed = fix_rules(language);

  // -> 8: 9 14 | 10 1 | 42 8
  // -> 11: 42 31 | 42 1000
  //    1000: 11 31
  auto const fixed_cnf = normalize(fixed);

  REQUIRE(fixed_cnf.contains(8));
  REQUIRE(fixed_cnf.at(8).size() == 3);
  REQUIRE(std::holds_alternative<Variables>(fixed_cnf.at(8)[0]));
  REQUIRE(std::holds_alternative<Variables>(fixed_cnf.at(8)[1]));
  REQUIRE(std::holds_alternative<Variables>(fixed_cnf.at(8)[2]));

  REQUIRE(std::get<Variables>(fixed_cnf.at(8)[0]).first == 9);
  REQUIRE(std::get<Variables>(fixed_cnf.at(8)[0]).second == 14);

  REQUIRE(std::get<Variables>(fixed_cnf.at(8)[1]).first == 10);
  REQUIRE(std::get<Variables>(fixed_cnf.at(8)[1]).second == 1);

  REQUIRE(std::get<Variables>(fixed_cnf.at(8)[2]).first == 42);
  REQUIRE(std::get<Variables>(fixed_cnf.at(8)[2]).second == 8);

  REQUIRE(fixed_cnf.contains(11));
  REQUIRE(fixed_cnf.at(11).size() == 2);
  REQUIRE(std::holds_alternative<Variables>(fixed_cnf.at(11)[0]));
  REQUIRE(std::holds_alternative<Variables>(fixed_cnf.at(11)[1]));

  REQUIRE(std::get<Variables>(fixed_cnf.at(11)[0]).first == 42);
  REQUIRE(std::get<Variables>(fixed_cnf.at(11)[0]).second == 31);

  REQUIRE(std::get<Variables>(fixed_cnf.at(11)[1]).first == 42);
  REQUIRE(std::get<Variables>(fixed_cnf.at(11)[1]).second == 1000);

  REQUIRE(fixed_cnf.contains(1000));
  REQUIRE(fixed_cnf.at(1000).size() == 1);
  REQUIRE(std::holds_alternative<Variables>(fixed_cnf.at(1000)[0]));

  REQUIRE(std::get<Variables>(fixed_cnf.at(1000)[0]).first == 11);
  REQUIRE(std::get<Variables>(fixed_cnf.at(1000)[0]).second == 31);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example2};
  auto const [language, messages] = parse_input(input);

  auto const fixed = fix_rules(language);
  auto const fixed_cnf = normalize(fixed);

  REQUIRE(is_valid(fixed_cnf, messages[3]));
  REQUIRE(not is_valid(fixed_cnf, messages[0]));

  auto const valid_fixed = count_valid(fixed_cnf, messages);
  REQUIRE(valid_fixed == 12);
}
