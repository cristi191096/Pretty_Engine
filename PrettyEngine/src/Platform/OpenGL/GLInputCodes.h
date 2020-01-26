#ifndef GL_INPUTS
	#define GL_INPUTS

#pragma once

//#include "engine\Core.h"

//Keys that matches GLFW. Otherwise convertion is needed.

namespace PrettyEngine {
	
	enum keyCode
	{
		NONE				=		 0,
		
		//Printable keys
		Space				=		 32,
		Apostrophe			=		 39, 
		Comma				=		 44, 
		Minus				=		 45, 
		Period				=		 46, 
		Slash				=		 47, 
		Alpha0				=		 48,
		Alpha1				=		 49,
		Alpha2				=		 50,
		Alpha3				=		 51,
		Alpha4				=		 52,
		Alpha5				=		 53,
		Alpha6				=		 54,
		Alpha7				=		 55,
		Alpha8				=		 56,
		Alpha9				=		 57,
		Semicolon			=		 59, 
		Equal				=		 61, 
		A					=		 65,
		B					=		 66,
		C					=		 67,
		D					=		 68,
		E					=		 69,
		F					=		 70,
		G					=		 71,
		H					=		 72,
		I					=		 73,
		J					=		 74,
		K					=		 75,
		L					=		 76,
		M					=		 77,
		N					=		 78,
		O					=		 79,
		P					=		 80,
		Q					=		 81,
		R					=		 82,
		S					=		 83,
		T					=		 84,
		U					=		 85,
		V					=		 86,
		W					=		 87,
		X					=		 88,
		Y					=		 89,
		Z					=		 90,
		LeftBracket			=		 91, 
		BackSlash			=		 92, 
		RightBracket		=		 93, 
		GraveAccent			=		 96, 
		World1				=		 161, 
		World2				=		 162, 
		
		//Function keys
		Escape				=		256,
		Enter				=		257,
		Tab					=		258,
		Backspace			=		259,
		Insert				=		260,
		Delete				=		261,
		RIGHT				=		262,
		LEFT				=		263,
		DOWN				=		264,
		UP					=		265,
		PageUP				=		266,
		PageDOWN			=		267,
		Home				=		268,
		End					=		269,
		CapsLock			=		280,
		ScrollLock			=		281,
		NumLock				=		282,
		PrintScreen			=		283,
		Pause				=		284,
		F1					=		290,
		F2					=		291,
		F3					=		292,
		F4					=		293,
		F5					=		294,
		F6					=		295,
		F7					=		296,
		F8					=		297,
		F9					=		298,
		F10					=		299,
		F11					=		300,
		F12					=		301,
		F13					=		302,
		F14					=		303,
		F15					=		304,
		F16					=		305,
		F17					=		306,
		F18					=		307,
		F19					=		308,
		F20					=		309,
		F21					=		310,
		F22					=		311,
		F23					=		312,
		F24					=		313,
		F25					=		314,
		KeyPad0				=		320,
		KeyPad1				=		321,
		KeyPad2				=		322,
		KeyPad3				=		323,
		KeyPad4				=		324,
		KeyPad5				=		325,
		KeyPad6				=		326,
		KeyPad7				=		327,
		KeyPad8				=		328,
		KeyPad9				=		329,
		KPDecimal			=		330,
		KPDivide			=		331,
		KPMultiply			=		332,
		KPSubtract			=		333,
		KPAdd				=		334,
		KPEnter				=		335,
		KPEqual				=		336,
		LeftShift			=		340,
		LeftControl			=		341,
		LeftAlt				=		342,
		LeftSuper			=		343,
		RightShift			=		344,
		RightControl		=		345,
		RightAlt			=		346,
		RightSuper			=		347,
		Menu				=		348

	};

	//Mouse Buttons
	enum Mouse
	{
		Button1				=		0,
		Button2				=		1,
		Button3				=		2,
		Button4				=		3,
		Button5				=		4,
		Button6				=		5,
		Button7				=		6,
		Button8				=		7,
		Left				=		0,
		Right				=		1,
		Middle				=		2
	};

	namespace Internal {
		enum action
		{
			NONE		=		0,
			Press		=		1,
			Repeat		=		2,
			Release		=		0
		};

		enum mod {
			None		=		0,
			Shift		=		0x0001,
			Control		=		0x0002,
			Alt			=		0x0004,
			Super		=		0x0008,
			CapsLock	=		0x0010,
			NumLock		=		0x0020
		};
	}
}

#endif // !GL_INPUTS