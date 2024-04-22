/*-------------------------------------------------------------------------
 *
 * sp.h
 *	  server page storage manager public interface declarations.
 *
 *
 * Portions Copyright (c) 1996-2019, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/storage/sp.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef SP_H
#define SP_H

#include "storage/block.h"
#include "storage/relfilenode.h"
#include "storage/smgr.h"
#include "storage/sync.h"

/* sp storage manager functionality */
extern void spinit(void);
extern void spclose(SMgrRelation reln, ForkNumber forknum);
extern void spcreate(SMgrRelation reln, ForkNumber forknum, bool isRedo);
extern bool spexists(SMgrRelation reln, ForkNumber forknum);
extern void spunlink(RelFileNodeBackend rnode, ForkNumber forknum, bool isRedo);
extern void spextend(SMgrRelation reln, ForkNumber forknum,
					 BlockNumber blocknum, char *buffer, bool skipFsync);
extern void spprefetch(SMgrRelation reln, ForkNumber forknum,
					   BlockNumber blocknum);
extern void spread(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum,
				   char *buffer);
extern void spwrite(SMgrRelation reln, ForkNumber forknum,
					BlockNumber blocknum, char *buffer, bool skipFsync);
extern void spwriteback(SMgrRelation reln, ForkNumber forknum,
						BlockNumber blocknum, BlockNumber nblocks);
extern BlockNumber spnblocks(SMgrRelation reln, ForkNumber forknum);
extern void sptruncate(SMgrRelation reln, ForkNumber forknum,
					   BlockNumber nblocks);
extern void spimmedsync(SMgrRelation reln, ForkNumber forknum);

extern void ForgetDatabaseSyncRequests(Oid dbid);
extern void DropRelationFiles(RelFileNode *delrels, int ndelrels, bool isRedo);

/* sp sync callbacks */
extern int	mdsyncfiletag(const FileTag *ftag, char *path);
extern int	mdunlinkfiletag(const FileTag *ftag, char *path);
extern bool mdfiletagmatches(const FileTag *ftag, const FileTag *candidate);

#endif							/* SP_H */
