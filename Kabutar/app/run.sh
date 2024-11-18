
./record_c_file

base64 recording.wav > audio_base64.txt

./speech_to_text_final

./matching_c_file > line.txt

./extractor > extractedWords.log

./dictionary > cmd.log 

cat cmd.log | bash 