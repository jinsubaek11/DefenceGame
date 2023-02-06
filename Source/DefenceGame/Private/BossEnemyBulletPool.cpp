#include "BossEnemyBulletPool.h"
#include "PooledBossEnemyBullet.h"


ABossEnemyBulletPool::ABossEnemyBulletPool()
{
	classType = APooledBossEnemyBullet::StaticClass();
	poolSize = 6;
}