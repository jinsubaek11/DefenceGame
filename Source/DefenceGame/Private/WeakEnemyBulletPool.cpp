#include "WeakEnemyBulletPool.h"
#include "PooledWeakEnemyBullet.h"


AWeakEnemyBulletPool::AWeakEnemyBulletPool()
{
	classType = APooledWeakEnemyBullet::StaticClass();
	poolSize = 5;
}