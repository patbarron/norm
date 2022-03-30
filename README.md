# USCF Title Norm Calculator

This is a simple program that calculates the norms that would be
awarded for a particular tournament performance.

This program is non-interactive, all input to the program is on
the command line.  The command line arguments are the player's
tournament score, followed by the post-tournament ratings of each
of the player's opponents.  For a game that is unplayed due to
a bye, forfeit win, or forfeit loss, use "0" as the opponent's
rating for that round.  The highest norm earned in the event
is printed to stdout; if no norm is earned, nothing is printed.

Calculations are based on the document "The US Chess Title System",
dated February 2016, located at http://www.glicko.net/ratings/titles.pdf.

Be aware that the calculation involving norms in events that include
an unplayed game is really not tested at all.
