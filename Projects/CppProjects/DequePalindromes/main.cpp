//------------------------------------------------------------------------------
//
// File Name:	main.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin), main() function from Udemy course
// Project:	PRG 8.2.7 Assignment: Palindrome using Deques
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include <cctype>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Determines if a given string is a palindrome
// Params:
//	 s = The string to check
// Returns:
//   if the string is a palindrome
bool is_palindrome(const std::string& s)
{
	// Two deques: one to hold the string in one direction, one to hold it in the other
    std::deque<char> forward;
	std::deque<char> backward;
    
    // For every alpha character, convert it to upercase and push it to the front or back of each deque
    for (auto it = s.begin(); it != s.end(); it++)
    {
        if (isalpha(*it))
        {
            forward.push_front(static_cast<char>(toupper(*it)));
            backward.push_back(static_cast<char>(toupper(*it)));
        }
    }

    // If the deques are the same, then the string is the same in both directions, thus being a palindrome
    return forward == backward;
}

int main()
{
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };
   
    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for(const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s)  << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}