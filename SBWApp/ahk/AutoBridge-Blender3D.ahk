; Copyright (C) 2014 Ricardo B. Santos
; Licensed under Simplified BSD License

#SingleInstance,Force
#MaxHotkeysPerInterval 240
CoordMode,Mouse,Screen

applicationname := "AutoBridge"

buttonM := 1
buttonB := 1
buttonC1 := 1
buttonC2 := 1

Gui,+Owner -Resize +ToolWindow -DPIScale 
Gui,Margin,2,4

Gui,Font,C000000 Q4 S10 w400,Tahoma
Gui,Add,Text,Vtext x16 y16 w320,

Gui,Show, w340 H60 NoActivate, %applicationname%
GuiControl,,text, SBW -> AutoBridge -> Target application

WM_SBEXPLORER := DllCall( "RegisterWindowMessage", Str, "SBExplorer" )
OnMessage( WM_SBEXPLORER, "SBEXPLORER" )

; WM_SBEXPLORER_QUERY := DllCall( "RegisterWindowMessage", Str, "SBExplorer_query" )

TrayTip, Information, Use Alt+Ctrl+Shift+Esc to suspend and pause this script, 5, 1

Return

SBEXPLORER( wParam,lParam ) {
	IfWinActive,Blender
	{
		 hWindow := lParam
		 
		 Tranlation := wParam & 0xFFFF
		 Rotation := (wParam >> 16) & 0xFFFF

		 TrOp := Tranlation & 0x3F
		 RtOp := Rotation & 0x3F
			
		 if (TrOp & 1)=1
		 {
			FUNC_FORWARD()
		 }
		 if (TrOp & 2)=2
		 {
			FUNC_BACK()
		 }
		 if (TrOp & 4)=4
		 {
			FUNC_RIGHT()
		 }
		  if (TrOp & 8)=8
		 {
			FUNC_LEFT()
		 }
		 if (TrOp & 16)=16
		 {
			FUNC_UP()
		 }
		 if (TrOp & 32)=32
		 {
			FUNC_DOWN()
		 }

		 if (RtOp & 1)=1
		 {
			FUNC_XROT1()
		 }
		 if (RtOp & 2)=2
		 {
			FUNC_XROT2()
		 }
		 if (RtOp & 4)=4
		 {
			FUNC_YROT1()
		 }
		 if (RtOp & 8)=8
		 {
			FUNC_YROT2()
		 }
		 if (RtOp & 16)=16
		 {
			FUNC_ZROT1()
		 }
		 if (RtOp & 32)=32
		 {
			FUNC_ZROT2()
		 }
	}
}

GuiClose:
ExitApp

FUNC_FORWARD()
{
	GetKeyState,mstate,LButton,P
	GetKeyState,mstate2,RButton,P
	if mstate=D
	{
		SendInput, {Esc}gy
	}
	else if mstate2=D
	{
		SendInput, {Esc}sy
	}
	else
	{
		SendInput, {LSHIFT down}{WheelDown}{LSHIFT up}
	}
}
FUNC_BACK()
{
	GetKeyState,mstate,LButton,P
	GetKeyState,mstate2,RButton,P
	if mstate=D
	{
		SendInput, {Esc}gy
	}
	else if mstate2=D
	{
		SendInput, {Esc}sy
	}
	else
	{
		SendInput, {LSHIFT down}{WheelUp}{LSHIFT up}
	}
}
FUNC_RIGHT()
{
	GetKeyState,mstate,LButton,P
	GetKeyState,mstate2,RButton,P
	if mstate=D
	{
		SendInput, {Esc}gx
	}
	else if mstate2=D
	{
		SendInput, {Esc}sx
	}
	else
	{
		SendInput,  {LCtrl down}{WheelDown}{LCtrl up}
	}
}
FUNC_LEFT()
{
	GetKeyState,mstate,LButton,P
	GetKeyState,mstate2,RButton,P
	if mstate=D
	{
		SendInput, {Esc}gx
	}
	else if mstate2=D
	{
		SendInput, {Esc}sx
	}
	else
	{
		SendInput,  {LCtrl down}{WheelUp}{LCtrl up}
	}
}
FUNC_UP()
{
	GetKeyState,mstate,LButton,P
	GetKeyState,mstate2,RButton,P
	if mstate=D
	{
		SendInput, {Esc}gz
	}
	else if mstate2=D
	{
		SendInput, {Esc}sz
	}
	else
	{
		SendInput, {WheelUp}
	}
}
FUNC_DOWN()
{
	GetKeyState,mstate,LButton,P
	GetKeyState,mstate2,RButton,P
	if mstate=D
	{
		SendInput, {Esc}gz
	}
	else if mstate2=D
	{
		SendInput, {Esc}sz
	}
	else
	{
		SendInput, {WheelDown}
	}
}

FUNC_XROT1()
{
	GetKeyState,mstate,LButton,P
	if mstate=D
	{
		SendInput, {Esc}rx
	}
	else
	{
		SendInput, {LSHIFT down}{LAlt down}{WheelUp}{LAlt up}{LSHIFT up}
	}
}
FUNC_XROT2()
{
	GetKeyState,mstate,LButton,P
	if mstate=D
	{
		SendInput, {Esc}rx
	}
	else
	{
		SendInput, {LSHIFT down}{LAlt down}{WheelDown}{LAlt up}{LSHIFT up}
	}
}
FUNC_YROT1()
{
	GetKeyState,mstate,LButton,P
	if mstate=D
	{
		SendInput, {Esc}ry
	}
	else
	{
		SendInput, {LSHIFT down}{LCtrl down}{WheelDown}{LCtrl up}{LSHIFT up}
	}
}
FUNC_YROT2()
{
	GetKeyState,mstate,LButton,P
	if mstate=D
	{
		SendInput, {Esc}ry
	}
	else
	{
		SendInput,{LSHIFT down}{LCtrl down}{WheelUp}{LCtrl up}{LSHIFT up}
	}
}
FUNC_ZROT1()
{
	GetKeyState,mstate,LButton,P
	if mstate=D
	{
		SendInput, {Esc}rz
	}
	else
	{
		SendInput, {LAlt down}{LCtrl down}{WheelUp}{LCtrl up}{LAlt up}
	}
}
FUNC_ZROT2()
{
	GetKeyState,mstate,LButton,P
	if mstate=D
	{
		SendInput, {Esc}rz
	}
	else
	{
		SendInput, {LAlt down}{LCtrl down}{WheelDown}{LCtrl up}{LAlt up}
	}
}

~!^+Esc::
	Suspend ;, Off
	Pause ;, Off
return

$F13::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
			SendInput, {LAlt down}{Home}{LAlt up}
		}
		else
		{
			SendInput, {SPACE}
		}
	}
	else
	{
		SendInput, {F13}
	}
return

$F14::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
			SendInput, {LCtrl down}i{LCtrl up}
		}
		else
		{
			SendInput, a
		}
	}
	else
	{
		SendInput, {F14}
	}
return

$LButton::
	IfWinActive,Blender
	{
		if buttonM=2
		{
			SendInput, {LShift down}{LButton down}
			return
		}
	}
	SendInput, {LButton down}
return

~LButton up::
	IfWinActive,Blender
	{
		if buttonM=2
		
		{
			SendInput, {LShift up}
		}
	}
return

~MButton::
	IfWinActive,Blender
	{
		if buttonM=1
		{
			buttonM:=2
		}
		else
		{
			buttonM:=1
		}
	}
return

~RButton::
	IfWinActive,Blender
	{
		buttonM:=1
		GetKeyState,mstate,LButton,P
		if mstate=D
		{
			SendInput, {LCtrl down}{LButton}{LCtrl up}
		}
	}
return

$XButton1::
	IfWinActive,Blender
	{
		SendInput, c
	}
	else
	{
		SendInput, {XButton1}
	}
return

$XButton2::
	IfWinActive,Blender
	{
		SendInput, b
	}
	else
	{
		SendInput, {XButton2}
	}
return

$F15::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
			SendInput, t
		}
		else
		{
			SendInput, n
		}
	}
	else
	{
		SendInput, {F15}
	}
return

$F16::
	IfWinActive,Blender
	{
		SendInput, w
	}
	else
	{
		SendInput, {F16}
	}
return

$F17::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
			SendInput, x
		}
		else
		{
			SendInput, {LSHIFT down}{LCtrl down}z{LCtrl up}{LSHIFT up}
		}
	}
	else
	{
		SendInput, {F17}
	}
return

$F18::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
			SendInput, {LAlt down}{LCtrl down}z{LCtrl up}{LAlt up}
		}
		else
		{
			SendInput, {LCtrl down}z{LCtrl up}
		}
	}
	else
	{
		SendInput, {F18}
	}
return

$F19::
	IfWinActive,Blender
	{
		;SendInput, F19{Enter}
	}
	else
	{
		SendInput, {F19}
	}
return

$F20::
	IfWinActive,Blender
	{
		;SendInput, F20{Enter}
	}
	else
	{
		SendInput, {F20}
	}
return

$F21::
	IfWinActive,Blender
	{
		;SendInput, F21{Enter}
	}
	else
	{
		SendInput, {F21}
	}
return

$F22::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
			SendInput, {LSHIFT down}s{LSHIFT up}
		}
		else
		{
			SendInput, {TAB}
		}
	}
	else
	{
		SendInput, {F22}
	}
return

$F23::
	IfWinActive,Blender
	{
		if buttonB=1
		{
			buttonB:=2
			SendInput, {Numpad1}
		}
		else
		{
			buttonB:=1
			SendInput, {LCtrl down}{Numpad1}{LCtrl up}
		}
	}
	else
	{
		SendInput, {F23}
	}
return

$F24::
	IfWinActive,Blender
	{
		GetKeyState,mstate,RButton,P
		if mstate=D
		{
		   if buttonC1=1
		   {
				buttonC1:=2
				SendInput, {Numpad3}
		   }
		   else
		   {
				buttonC1:=1
				SendInput, {LCtrl down}{Numpad3}{LCtrl up}
		   }
		}
		else
		{
			if buttonC2=1
			{
				buttonC2:=2
				SendInput, {Numpad7}
			}
			else
			{
				buttonC2:=1
				SendInput, {LCtrl down}{Numpad7}{LCtrl up}
			}
		}
	}
	else
	{
		SendInput, {F24}
	}
return
