#!/usr/bin/env python
#

# import modules used here
import sys
import argparse
# https://docs.python.org/2/library/argparse.html

import logging

# Gather our code in a main() function
def main(args, loglevel):
  logging.basicConfig(format="%(levelname)s: %(message)s", level=loglevel)
  logging.debug("Your Argument: %s, %s" % (args.com, args.baudrate))
  # Now can use the parameters in your source code now.
 
# Standard boilerplate to call the main() function to begin
# the program.
if __name__ == '__main__':
  parser = argparse.ArgumentParser( 
                                    description = "A python commandline template demonstrates how to parse the arguments",
                                    epilog = "If would like to display additional description of the program after the description of the arguments, add the text here.",
                                    fromfile_prefix_chars = '@' )
  # TODO Specify your real parameters here.
  parser.add_argument(
                      "-v",
                      "--version",
                      action='version',
                      version='%(prog)s 0.1',
                      help="Get the version information of the script.")

  # parser.add_argument("-v", "--verbose", 
  #                     help="increase output verbosity",
  #                     action="store_true")

  parser.add_argument(
                    "-c",
                    "--com",
                    default="192",
                    help="Specify the COM port.")

  parser.add_argument(
                    "-b",
                    "--baudrate",
                    default="115200",
                    help="Specify the baudrate for the COM port.")

  args = parser.parse_args()
  
  # Setup logging
  if True:
    loglevel = logging.DEBUG
  else:
    loglevel = logging.INFO
  
  main(args, loglevel)