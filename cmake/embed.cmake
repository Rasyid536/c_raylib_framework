file(READ "${INPUT}" hex_data HEX)
string(REGEX REPLACE "(..)" "0x\\1," hex_data "${hex_data}")
file(WRITE "${OUTPUT}"
  "// GENERATED FILE - DO NOT EDIT\n#pragma once\n"
  "static const unsigned char ${SYMBOL}[] = { ${hex_data} };\n"
  "static const unsigned int ${SYMBOL}_size = sizeof(${SYMBOL});\n")
