#ifndef NTRU_NTRU_H
#define NTRU_NTRU_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus*/

#include "types.h"
#include "key.h"
#include "encparams.h"
#include "rand.h"
#include "err.h"

/**
 * @brief Key generation
 *
 * Generates a NtruEncrypt key pair.
 * If a deterministic RNG is used, the key pair will be deterministic for a given random seed;
 * otherwise, the key pair will be completely random.
 *
 * @param params the NtruEncrypt parameters to use
 * @param kp pointer to write the key pair to (output parameter)
 * @param rand_ctx an initialized random number generator. See ntru_rand_init() in rand.h.
 * @return NTRU_SUCCESS for success, or a NTRU_ERR_ code for failure
 */
uint8_t ntru_gen_key_pair(NtruEncParams *params, NtruEncKeyPair *kp, NtruRandContext *rand_ctx);

/**
 * @brief Encryption
 *
 * Encrypts a message.
 * If a deterministic RNG is used, the encrypted message will also be deterministic for a given
 * combination of plain text, key, and random seed.
 * See P1363.1 section 9.2.2.
 *
 * @param msg The message to encrypt
 * @param msg_len length of msg. Must not exceed ntru_max_msg_len(params). To encrypt
 *                bulk data, encrypt with a symmetric key, then NTRU-encrypt that key.
 * @param pub the public key to encrypt the message with
 * @param params the NtruEncrypt parameters to use
 * @param rand_ctx an initialized random number generator. See ntru_rand_init() in rand.h.
 * @param enc output parameter; a pointer to store the encrypted message. Must accommodate
              ntru_enc_len(params) bytes.
 * @return NTRU_SUCCESS on success, or one of the NTRU_ERR_ codes on failure
 */
uint8_t ntru_encrypt(uint8_t *msg, uint16_t msg_len, NtruEncPubKey *pub, NtruEncParams *params, NtruRandContext *rand_ctx, uint8_t *enc);

/**
 * @brief Decryption
 *
 * Decrypts a message.
 * See P1363.1 section 9.2.3.
 *
 * @param enc The message to decrypt
 * @param kp a key pair that contains the public key the message was encrypted
             with, and the corresponding private key
 * @param params the NtruEncrypt parameters the message was encrypted with
 * @param dec output parameter; a pointer to store the decrypted message. Must accommodate
              ntru_max_msg_len(params) bytes.
 * @param dec_len output parameter; pointer to store the length of dec
 * @return NTRU_SUCCESS on success, or one of the NTRU_ERR_ codes on failure
 */
uint8_t ntru_decrypt(uint8_t *enc, NtruEncKeyPair *kp, NtruEncParams *params, uint8_t *dec, uint16_t *dec_len);

/**
 * @brief Maximum message length
 *
 * Returns the maximum length a plaintext message can be.
 * Depending on the parameter set, the maximum lengths for the predefined
 * parameter sets are between 60 and 248.
 * For longer messages, use hybrid encryption.
 *
 * @param params an NtruEncrypt parameter set
 * @return the maximum number of bytes in a message
 */
uint8_t ntru_max_msg_len(NtruEncParams *params);

#ifdef __cplusplus
}
#endif /* __cplusplus*/

#endif   /* NTRU_NTRU_H */
