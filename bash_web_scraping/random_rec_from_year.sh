#!/usr/bin/env bash

requested_year=$1
n_albums=$(wc -l < ${requested_year}_rym_top_rated_albums.txt)
random_album_index=$(( $RANDOM % $n_albums ))

echo "Random album #${random_album_index}"

sed -n "${random_album_index}p" ${requested_year}_rym_top_rated_albums.txt

