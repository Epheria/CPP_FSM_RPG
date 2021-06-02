#pragma once
#include <string>

enum
{
	ent_Player_Bob,
	ent_Player_Elsa
};

inline std::string GetNameOfEntity(int value)
{
	switch (value)
	{
	case ent_Player_Bob: return "Bob";
	case ent_Player_Elsa: return "Elsa";
	default: return "Unknown!";
	}
}