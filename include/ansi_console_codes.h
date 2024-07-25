#ifndef _ANSI_CONSOLE_CODES_H_
#define _ANSI_CONSOLE_CODES_H_

/**
 * \file
 * Common console escape code definitions for easy usage.
 *
 * More inforamtion regarding the codes and control sequences can be found on
 * https://en.wikipedia.org/wiki/ANSI_escape_code#Description
 */

/**
 *  Control Characters
 */
#define BEL "\a"   /** Bell control character */
#define BS  "\b"   /** Backspace control character */
#define HT  "\t"   /** Tab control character */
#define LF  "\n"   /** Line feed control character */
#define FF  "\f"   /** Form feed control character */
#define CR  "\r"   /** Carriage return control character */
#define ESC "\033" /** Escape control character */

/**
 * ANSI escape sequences
 */
#define ANSI_ESCAPE(x) ESC x /** Common ANSI escape sequence */

#define SS2 ANSI_ESCAPE("N")  /** Single Shift Two escape sequence */
#define SS3 ANSI_ESCAPE("O")  /** Single Shift Three escape sequence */
#define DCS ANSI_ESCAPE("P")  /** Device control string escape sequence */
#define CSI ANSI_ESCAPE("[")  /** Control Sequence Introducer escape sequence */
#define ST  ANSI_ESCAPE("\\") /** String Terminator escape sequence */
#define OSC ANSI_ESCAPE("]")  /** Operating System Command escape sequence */
#define SOS ANSI_ESCAPE("X")  /** Start of String escape sequence */
#define PM  ANSI_ESCAPE("^")  /** Privacy Message escape sequence */
#define APC ANSI_ESCAPE("_")  /** Application Program Command escape sequence */

/**
 * ANSI control sequences
 */
#define CUU(n)    CSI #n "A"        /** Cursor up */
#define CUU_      CSI "A"           /** Cursor 1 up */
#define CUD(n)    CSI #n "B"        /** Cursor down */
#define CUD_      CSI "B"           /** Cursor 1 down */
#define CUF(n)    CSI #n "C"        /** Cursor forward */
#define CUF_      CSI "C"           /** Cursor 1 forward */
#define CUB(n)    CSI #n "D"        /** Cursor back */
#define CUB_      CSI "D"           /** Cursor 1 back */
#define CNL(n)    CSI #n "E"        /** Cursor to beginning of line n down */
#define CNL_      CSI "E"           /** Cursor to beginning of line 1 down */
#define CPL(n)    CSI #n "F"        /** Cursor to beginning of line n up */
#define CPL_      CSI "F"           /** Cursor to beginning of line 1 up */
#define CHA(n)    CSI #n "G"        /** Cursor to column n */
#define CHA_      CSI "G"           /** Cursor to column 1 */
#define CUP(n, m) CSI #n ";" #m "H" /** Move cursor to row n column m */
#define CUP_      CSI "H"           /** Move cursor to top left corner */
#define ED(n)     CSI #n "J"        /** Erase in display */
#define ED_       CSI "J"           /** Erase in display from cursor to end */
#define EL(n)     CSI #n "K"        /** Erase in line */
#define EL_       CSI "K"           /** Erase in line from cursor to end */
#define SU(n)     CSI #n "S"        /** Scroll whole page up n lines */
#define SU_       CSI "S"           /** Scroll whole page up 1 line */
#define SD(n)     CSI #n "T"        /** Scroll whole page down n lines */
#define SD_       CSI "T"           /** Scroll whole page down 1 line */
#define SGR(n)    CSI #n "m"        /** Select graphic rendition */

#define SCP CSI "s" /** Save cursor position */
#define RCP CSI "u" /** Recall cursor position */

/**
 * SGR parameters
 */
#define ANSI_RESET SGR(0) /** Reset console to normal */

#define ANSI_BOLD   SGR(1)  /** Bold or increased intensity text */
#define ANSI_FAINT  SGR(2)  /** Faint or decreased intensity text */
#define ANSI_NORMAL SGR(22) /** Normal intensity text */

#define ANSI_ITALIC    SGR(3)  /** Italic text */
#define ANSI_NO_ITALIC SGR(23) /** Disable Italic */

#define ANSI_UNDERLINE    SGR(4)  /** Underline text */
#define ANSI_NO_UNDERLINE SGR(24) /** Disable Underline */

#define ANSI_INVERT    SGR(7)  /** Swap foreground and background colors */
#define ANSI_NO_INVERT SGR(27) /** Disable invert */

#define ANSI_STRIKE    SGR(9)  /** Strikeout text */
#define ANSI_NO_STRIKE SGR(29) /** Disable strikeout */

#define ANSI_CONCEAL    SGR(8)  /** Conceal text */
#define ANSI_NO_CONCEAL SGR(28) /** Disable conceal */

/**
 * Colors
 */
#define BLACK   0 /** Black console color */
#define RED     1 /** Red console color */
#define GREEN   2 /** Green console color */
#define YELLOW  3 /** Yello console color */
#define BLUE    4 /** Blue console color */
#define MAGENTA 5 /** Magenta console color */
#define CYAN    6 /** Cyan console color */
#define WHITE   7 /** White console color */

#define COLOR_CODE(setting, color) SGR(setting##color) /** Color code escape code helper */

#define ANSI_FG(color)        COLOR_CODE(3, color)  /** Foreground color escape sequence */
#define ANSI_BG(color)        COLOR_CODE(4, color)  /** Background color escape sequence */
#define ANSI_BRIGHT_FG(color) COLOR_CODE(9, color)  /** Bright foreground color escape sequence */
#define ANSI_BRIGHT_BG(color) COLOR_CODE(10, color) /** Bright background color escape sequence */

#define ANSI_DEFAULT_FG SGR(39) /** Default foreground color */
#define ANSI_DEFAULT_BG SGR(49) /** Default background color */

#define CLEAR_SCREEN CUP_ ED_ /** Control sequence to clear the screen and place cursor at the start of the screen */

#endif
