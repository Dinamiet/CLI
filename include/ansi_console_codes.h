#ifndef _ANSI_CONSOLE_CODES_H_
#define _ANSI_CONSOLE_CODES_H_

// https://en.wikipedia.org/wiki/ANSI_escape_code#Description

// Control Characters
#define BEL "\a"
#define BS	"\b"
#define HT	"\t"
#define LF	"\n"
#define FF	"\f"
#define CR	"\r"
#define ESC "\e"

// ANSI escape sequences
#define ANSI_ESCAPE(x) ESC x

#define SS2 ANSI_ESCAPE("N")
#define SS3 ANSI_ESCAPE("O")
#define DCS ANSI_ESCAPE("P")
#define CSI ANSI_ESCAPE("[")
#define ST	ANSI_ESCAPE("\\")
#define OSC ANSI_ESCAPE("]")
#define SOS ANSI_ESCAPE("X")
#define PM	ANSI_ESCAPE("^")
#define APC ANSI_ESCAPE("_")

// ANSI control sequences
#define CUU(n)	  CSI #n "A"		// Cursor up
#define CUU_	  CSI "A"			// Cursor 1 up
#define CUD(n)	  CSI #n "B"		// Cursor down
#define CUD_	  CSI "B"			// Cursor 1 down
#define CUF(n)	  CSI #n "C"		// Cursor forward
#define CUF_	  CSI "C"			// Cursor 1 forward
#define CUB(n)	  CSI #n "D"		// Cursor back
#define CUB_	  CSI "D"			// Cursor 1 back
#define CNL(n)	  CSI #n "E"		// Cursor to beginning of line n down
#define CNL_	  CSI "E"			// Cursor to beginning of line 1 down
#define CPL(n)	  CSI #n "F"		// Cursor to beginning of line n up
#define CPL_	  CSI "F"			// Cursor to beginning of line 1 up
#define CHA(n)	  CSI #n "G"		// Cursor to column n
#define CHA_	  CSI "G"			// Cursor to column 1
#define CUP(n, m) CSI #n ";" #m "H" // Move cursor to row n column m
#define CUP_	  CSI "H"			// Move cursor to top left corner
#define ED(n)	  CSI #n "J"		// Erase in display
#define ED_		  CSI "J"			// Erase in display from cursor to end
#define EL(n)	  CSI #n "K"		// Erase in line
#define EL_		  CSI "K"			// Erase in line from cursor to end
#define SU(n)	  CSI #n "S"		// Scroll whole page up n lines
#define SU_		  CSI "S"			// Scroll whole page up 1 line
#define SD(n)	  CSI #n "T"		// Scroll whole page down n lines
#define SD_		  CSI "T"			// Scroll whole page down 1 line
#define SGR(n)	  CSI #n "m"		// Select graphic rendition

#define SCP CSI "s" // Save cursor position
#define RCP CSI "u" // Recall cursor position

// SGR parameters
#define ANSI_RESET SGR(0)

#define ANSI_BOLD	SGR(1)
#define ANSI_FAINT	SGR(2)
#define ANSI_NORMAL SGR(22)

#define ANSI_ITALIC	   SGR(3)
#define ANSI_NO_ITALIC SGR(23)

#define ANSI_UNDERLINE	  SGR(4)
#define ANSI_NO_UNDERLINE SGR(24)

#define ANSI_INVERT	   SGR(7)
#define ANSI_NO_INVERT SGR(27)

#define ANSI_STRIKE	   SGR(9)
#define ANSI_NO_STRIKE SGR(29)

#define ANSI_CONCEAL	SGR(8)
#define ANSI_NO_CONCEAL SGR(28)

// Colors
#define BLACK	0
#define RED		1
#define GREEN	2
#define YELLOW	3
#define BLUE	4
#define MAGENTA 5
#define CYAN	6
#define WHITE	7

#define COLOR_CODE(setting, color) SGR(setting##color)

#define ANSI_FG(color)		  COLOR_CODE(3, color)
#define ANSI_BG(color)		  COLOR_CODE(4, color)
#define ANSI_BRIGHT_FG(color) COLOR_CODE(9, color)
#define ANSI_BRIGHT_BG(color) COLOR_CODE(10, color)

#define ANSI_DEFAULT_FG SGR(39)
#define ANSI_DEFAULT_BG SGR(49)

#endif
