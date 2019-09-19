#include "HitableList.h"
#include "util.h"

int hlist_hit(void* hlist_ptr, const Ray* ray, float tmin, float tmax, HitRecord* record);

void hlist_free_func(Hitable* hitable_ptr)
{
	hlist_free((HitableList*)hitable_ptr);
}

HitableList hlist_create(Hitable** list, unsigned int size)
{
	return (HitableList){hlist_hit, hlist_free_func, list, size};
}

HitableList* hlist_new(unsigned int size)
{
	HitableList* hlist = ALLOC_NEW(HitableList, 1);

	hlist->hit = hlist_hit;
	hlist->free = hlist_free_func;
	hlist->list = ALLOC_NEW(Hitable*, size);
	hlist->size = size;

	return hlist;
}

HitableList* hlist_newl(Hitable** list, unsigned int size)
{
	HitableList* hlist = ALLOC_NEW(HitableList, 1);

	hlist->hit = hlist_hit;
	hlist->free = hlist_free_func;
	hlist->list = list;
	hlist->size = size;

	return hlist;
}

void hlist_free(HitableList* hlist)
{
	for(int i = 0;i < hlist->size;++i)
	{
		Hitable* hitable = hlist->list[i];
		hitable->free(hitable);
	}

	free(hlist->list);
	free(hlist);
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