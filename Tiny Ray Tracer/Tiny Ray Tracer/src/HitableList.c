#include "HitableList.h"

int hlist_hit(void* hlist_ptr, const Ray* ray, float tmin, float tmax, HitRecord* record);

HitableList hlist_create(Hitable** list, unsigned int size)
{
	return (HitableList){hlist_hit, list, size};
}

int hlist_hit(void* hlist_ptr, const Ray* ray, float tmin, float tmax, HitRecord* record)
{
	HitableList* hlist = (HitableList*)hlist_ptr;

	HitRecord tmp_record;
	int hit_anything = FALSE;
	double closest_so_far = tmax;

	for(int i = 0;i < hlist->size;++i)
	{
		Hitable* hitable = hlist->list[i];
		if(hitable->hit(hitable, ray, tmin, closest_so_far, &tmp_record))
		{
			hit_anything = TRUE;
			closest_so_far = tmp_record.t;
			// Copy tmp_record to record
			*record = tmp_record;
		}
	}

	return hit_anything;
}