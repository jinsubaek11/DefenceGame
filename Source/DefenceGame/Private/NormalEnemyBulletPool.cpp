#include "NormalEnemyBulletPool.h"
#include "PooledNormalEnemyBullet.h"


ANormalEnemyBulletPool::ANormalEnemyBulletPool()
{
	classType = APooledNormalEnemyBullet::StaticClass();
	poolSize = 5;
}