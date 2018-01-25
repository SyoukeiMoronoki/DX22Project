#include "BossBrainTable.h"

#include "BossBrain_Crawl.h"
#include "BossBrain_Chase.h"
#include "BossBrain_Around.h"
#include "BossBrain_Jump.h"

static BossBrain_Crawl CRAWL;
static BossBrain_Chase CHASE;
static BossBrain_Around AROUND;
static BossBrain_Jump JUMP;

static BossBrain* BRAINS[BossBrainTable::BRAIN_DATANUM] =
{
  &CRAWL,
  &CHASE,
  &AROUND,
  &JUMP,
};

BossBrain* BossBrainTable::GetBossBrain(T_UINT8 brain)
{
  return BRAINS[brain];
}
