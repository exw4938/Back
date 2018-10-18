/**
 * file: local.h
 * contributors: Ellis Wright
 * description: Provides definitions for functions for manipulating
 * and working with local files
 */

#ifndef _LOCAL_H_
#define _LOCAL_H_

#include "config.h"

/**
 * Backs up the file to the remote server using scp.
 *
 * filename: the name of the file to be backed up
 */
void backupfile(Config* conf, char* filename);

/**
 * Runs a full backup by collecting all the values in the .backup file,
 * placing them in a tar archive, then transferring them to the remote server.
 *
 * parameters:
 *      conf - A pointer to the config file
 *
 * return:
 *      Returns 0 if the operation suceeded 1 if it failed
 */
int run_backup(Config* conf);


/**
 * Adds the file specified by filename to the .backup file
 *
 * parameters:
 *      filename - The name and FULL PATH of the file to add
 *      conf - A pointer to the config information
 *
 * return:
 *      Returns a 0 if the operation suceeded and 1 if it failed.
 */
int add_file(Config* conf, char* filename);

#endif
