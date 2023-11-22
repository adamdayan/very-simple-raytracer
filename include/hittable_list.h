#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>

#include "hittable.h"

class HittableList : public Hittable {
  public:
    HittableList() {}
    HittableList(const std::vector<std::shared_ptr<Hittable>>& hittables) : hittables(hittables) {} // NOTE: work out why this doesn't work :(


    void add(std::shared_ptr<Hittable> hittable) {
      hittables.push_back(hittable);
    }

    void clear() {
      hittables.clear();
    }

    bool hit(const Ray& r, const Interval& t_interval, HitRecord& rec) const override {
      double cur_min_t = t_interval.max;
      HitRecord cur_rec{};
      bool is_hit = false;

      for (const auto& hittable : hittables) {
        if (hittable->hit(r, Interval(t_interval.min, cur_min_t), cur_rec)) {
          is_hit = true;
          if (cur_rec.t < cur_min_t) {
            cur_min_t = cur_rec.t;
          }
        }
      }

      rec = cur_rec;
      return is_hit;
    }
  private:
    std::vector<std::shared_ptr<Hittable>> hittables;
};


#endif // HITTABLE_LIST_H