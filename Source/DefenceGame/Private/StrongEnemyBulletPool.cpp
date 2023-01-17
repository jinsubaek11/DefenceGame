#include "StrongEnemyBulletPool.h"
#include "PooledStrongEnemyBullet.h"


AStrongEnemyBulletPool::AStrongEnemyBulletPool()
{
	classType = APooledStrongEnemyBullet::StaticClass();
	poolSize = 5;
}