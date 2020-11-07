for((i=0;i<10;i++)); do
    echo $i
    ./bonus < input_0$i.txt
done

for((i=10;i<12;i++)); do
    echo $i
    ./bonus < input_$i.txt
done
