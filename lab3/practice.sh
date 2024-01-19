find . -type f -name '*.txt' -print0 | while IFS= read -r -d '' f; do
  mv -- "$f" "${f%.txt}.text"
done
