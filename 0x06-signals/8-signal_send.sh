#!/bin/sh
# Send SIGQUIT signal to the passed pro-cess id
if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <pid>"
	exit 1
fi
kill -QUIT "$1"
