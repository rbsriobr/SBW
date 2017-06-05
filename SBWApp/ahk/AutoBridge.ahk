; Copyright (C) 2014 Ricardo B. Santos
; Licensed under Simplified BSD License

#SingleInstance,Force
#MaxHotkeysPerInterval 240
CoordMode,Mouse,Screen

applicationname := "AutoBridge"

Gui,+Owner -Resize +ToolWindow -DPIScale 
Gui,Margin,2,4

Gui,Font,C000000 Q4 S10 w400,Tahoma
Gui,Add,Text,Vtext x16 y16 w320,

Gui,Show, w340 H60 NoActivate, %applicationname%
GuiControl,,text, SBW -> AutoBridge -> Target application

WM_SBEXPLORER := DllCall( "RegisterWindowMessage", Str, "SBExplorer" )
OnMessage( WM_SBEXPLORER, "SBEXPLORER" )

; WM_SBEXPLORER_QUERY := DllCall( "RegisterWindowMessage", Str, "SBExplorer_query" )

Return

SBEXPLORER( wParam,lParam ) {
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

GuiClose:
ExitApp

FUNC_FORWARD()
{
	MsgBox, Forward
}
FUNC_BACK()
{
	MsgBox, Back
}
FUNC_RIGHT()
{
	MsgBox, Right
}
FUNC_LEFT()
{
	MsgBox, Left
}
FUNC_UP()
{
	MsgBox, Up
}
FUNC_DOWN()
{
	MsgBox, Down
}

FUNC_XROT1()
{
	MsgBox, XRot1
}
FUNC_XROT2()
{
	MsgBox, XRot2
}
FUNC_YROT1()
{
	MsgBox, YRot1
}
FUNC_YROT2()
{
	MsgBox, YRot2
}
FUNC_ZROT1()
{
	MsgBox, ZRot1
}
FUNC_ZROT2()
{
	MsgBox, ZRot2
}

F13::
	MsgBox, F13
return

F14::
	MsgBox, F14
return

F15::
	MsgBox, F15
return

F16::
	MsgBox, F16
return

F17::
	MsgBox, F17
return

F18::
	MsgBox, F18
return

F19::
	MsgBox, F19
return

F20::
	MsgBox, F20
return

F21::
	MsgBox, F21
return

F22::
	MsgBox, F22
return

F23::
	MsgBox, F23
return

F24::
	MsgBox, F24
return
