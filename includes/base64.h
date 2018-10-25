#ifndef BASE64_H
# define BASE64_H

# define DECODED_SIZE 300
# define ENCODED_SIZE 400

void	base64_encode_file_to_file(int input, int output);
int		base64_decode_file_to_file(int input, int output);

#endif