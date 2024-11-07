#!/bin/sh

if [ "$#" -ne 1 ]; then
	printf "Usage: %s <pid>\n" "$0"
	exit 1
fi

kill -SIGQUIT "$1"