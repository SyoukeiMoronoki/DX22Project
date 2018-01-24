#include "BossBrainTable.h"

#include "BossBrain_Crawl.h"

static BossBrain_Crawl CRAWL;

static BossBrain* BRAINS[BossBrainTable::BRAIN_DATANUM] =
{
  &CRAWL,
};

BossBrain* BossBrainTable::GetBossBrain(T_UINT8 brain)
{
  return BRAINS[brain];
}
