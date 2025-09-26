/*
 _ ____ __ ___ __  
| '_ \ V  V / '  \ 
| .__/\_/\_/|_|_|_|
|_|                

picowm is written by Egon Szabó <szegon@tuta.io> in 2025

Controls: Super+LMB move | Super+RMB resize
Build: cc -std=c99 -O2 -s -o pwm pwm.c -lX11
*/
#include<X11/Xlib.h>
#define M(a,b)((a)>(b)?(a):(b))
int main(){Display*d=XOpenDisplay(0);if(!d)return 1;Window r=DefaultRootWindow(d);XButtonEvent s={0};XWindowAttributes a;XEvent e;
XGrabButton(d,1,Mod4Mask,r,0,ButtonPressMask|ButtonReleaseMask|PointerMotionMask,GrabModeAsync,GrabModeAsync,0,0);
XGrabButton(d,3,Mod4Mask,r,0,ButtonPressMask|ButtonReleaseMask|PointerMotionMask,GrabModeAsync,GrabModeAsync,0,0);
for(;;){XNextEvent(d,&e);
 if(e.type==ButtonPress&&e.xbutton.subwindow){XGetWindowAttributes(d,e.xbutton.subwindow,&a);s=e.xbutton;}
 else if(e.type==MotionNotify&&s.subwindow){int dx=e.xmotion.x_root-s.x_root,dy=e.xmotion.y_root-s.y_root;
  s.button==1?XMoveWindow(d,s.subwindow,a.x+dx,a.y+dy):XResizeWindow(d,s.subwindow,M(1,a.width+dx),M(1,a.height+dy));}
 else if(e.type==ButtonRelease)s.subwindow=0;}
}
