#!/usr/bin/env bash

if [[ $# -eq 0 ]]; then
	echo 'Please provide a year (provide 0 to search for top rated albums of all time)'
	exit 0 
fi 


if [ $1 -eq 0 ]; then
	requested_year=""
	file_year="all_time"
else
	requested_year=$1
	file_year=$1
fi


getPageData() {
	echo "entering getPageData()"
	if [ $1 == 1 ]; then
		page_num=""
	else
		page_num="$1/"
	fi
	echo "page_num=${page_num}"

	echo "Attempting to curl data for page $1" 

	curl "https://rateyourmusic.com/charts/top/album/${requested_year}/${page_num}" \
	  -H 'accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7' \
	  -H 'cache-control: max-age=0' \
	  -b 'FCCDCF=%5Bnull%2Cnull%2Cnull%2C%5B%22CQZVOgAQZVOgAEsACBENCAFgAAAAAEPgACiQAAAWkSD-F-a2mLP8WCvwXYIcxCvrbAC1YhAAAkDBsACmHUtwAgFpoBkSJEEAEwAMAABQGiCQAAQEBAACIECAQAAQAAIAIAgAAAQQQABAAYAAEAAAACUAQRAIAAyCEAgIAgpEhAQAQQIkJFAkDABRmAAEAAgACAgEQQAMAKIgAAhBMQgSKCVoQaAAIECBAAABDEGCARKUqAYQAAICQACoCBAKAACyIAGgAgAAUATQQIAkCYEiHAghKiAA%22%2C%222~~dv.70.89.93.108.122.147.149.161.184.196.236.259.311.313.314.323.358.415.442.486.494.495.540.574.723.827.864.938.981.1029.1031.1040.1047.1048.1051.1067.1092.1095.1097.1126.1186.1205.1215.1276.1301.1329.1365.1415.1449.1514.1516.1570.1577.1579.1598.1616.1651.1697.1703.1716.1735.1753.1765.1870.1878.1889.1917.1958.1967.1985.2052.2072.2074.2213.2225.2253.2299.2328.2331.2336.2373.2415.2427.2506.2517.2526.2531.2568.2571.2575.2624.2628.2677.2770.2778.2822.2844.2867.2878.2884.2887.2894.2898.3008.3126.3172.3186.3222.3233.3234%22%2C%222D041720-1405-4A5F-AD60-E43A16605931%22%5D%5D; ulv=ygHAO7vCOe%2eby%2ffj%2fMfEacttZajPr62zMMcUHV7%2f284kxolj%2fDzyKIccYA%2eHobjk1594679090210590; is_logged_in=1; username=sethdp; sec_bs=31932a6ed2c3cddbb3279a5e805ff5b1; sec_ts=1760546370; sec_id=094432ef89e7ef92a7146f1c74cd017a; cf_clearance=ugm1Z1eNY6FlquiL0uefWJPTV5hai0I_1nuoJBo34kg-1760546403-1.2.1.1-vX6ofh43h2uSdzF4aK_oArZXmNunOWvvG_Pa4cz9PoWSTfNJQygMakQalZJal2bCGcdcd9Wb94W.pqA6RauKzh0qTahEyOj3zRO6G0ckjQRRxibnYPI5puinfRnP0evo9mX_AFCJQY4T6WAGL2HHlEs9bBss83PQZ7Di8KmRgvzY8KRAp2DBo_oWnze7syUXf7fgr5ZvmZTN2DagjUjGQUQ5bD_taVfKEYd9IiQl7ygRRI_z2SdHiDy6aEnTmKS3' \
	  -H 'priority: u=0, i' \
	  -H 'sec-ch-ua: "Chromium";v="140", "Not=A?Brand";v="24", "Google Chrome";v="140"' \
	  -H 'sec-ch-ua-arch: "x86"' \
	  -H 'sec-ch-ua-bitness: "64"' \
	  -H 'sec-ch-ua-full-version: "140.0.7339.214"' \
	  -H 'sec-ch-ua-full-version-list: "Chromium";v="140.0.7339.214", "Not=A?Brand";v="24.0.0.0", "Google Chrome";v="140.0.7339.214"' \
	  -H 'sec-ch-ua-mobile: ?0' \
	  -H 'sec-ch-ua-model: ""' \
	  -H 'sec-ch-ua-platform: "macOS"' \
	  -H 'sec-ch-ua-platform-version: "13.7.8"' \
	  -H 'sec-fetch-dest: document' \
	  -H 'sec-fetch-mode: navigate' \
	  -H 'sec-fetch-site: same-origin' \
	  -H 'sec-fetch-user: ?1' \
	  -H 'upgrade-insecure-requests: 1' \
	  -H 'user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/140.0.0.0 Safari/537.36' 

	echo "Exited curl command"
}

> ${file_year}_rym_charts_albums.txt
for ((i=1 ; i<=10 ; i++)); do
	echo -e "\nAttempting to retrive data for page ${i}:"
	getPageData $i | grep -o "alt=\".*, Cover art\"" | sed 's/alt=\"//;s/, Cover art\"//' >> ${file_year}_rym_top_rated_albums.txt 
done

echo 'Now run "./random_rec_from_year.sh <desired_year>" to get a random recommendation of a top rated album from your desired year!'
