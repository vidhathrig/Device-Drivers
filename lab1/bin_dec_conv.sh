#Program which converts decimal to binary and binary to decimal

for ((i=32;i>=0;i--)); do 
        r=$(( 2**$i)) 
        powers+=( $r  ) 
done 

s = 0
 
echo -e "Enter choice \n 1:Binary to decimal\n2:decimal to binary"
read choice

if [ $choice -eq 1 ]
	then
	echo -e "Enter binary number"
	read Binary

	Bnumber=$Binary 
	Decimal=0 
	power=1 
	while [ $Binary -ne 0 ] 
	do 
		rem=$(expr $Binary % 10 ) 
		Decimal=$((Decimal+(rem*power))) 
		power=$((power*2)) 
		Binary=$(expr $Binary / 10) 
	done
	echo "Decimal equivalent of $Bnumber :"
	echo  "$Decimal" 

elif [ $choice -eq 2 ]
	then
	echo "Enter the decimal number"
	read dec

	echo "The binary equivalent of $dec is:"

	for n in ${powers[@]}
	do
		if [[ $dec -lt ${n} ]] && [[ $s -eq 1 ]]
			then
			echo -n 0
		elif [ $dec -ge ${n} ]
			then
			echo -n 1
			s=1
			dec=$(( $dec - ${n} ))
		fi
	done

else
	echo "Invalid choice"
fi 