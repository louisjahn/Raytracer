#include <sstream>
#include <fstream>
#include <thread>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "utils.h"
#include "hittable_list.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "camera.h"
#include "metal.h"
#include "lambertian.h"
#include "dielectric.h"

color ray_color(const ray& r, const hittable_list &world, size_t depth) {
    hit_record rec;

    if (depth < 1)
        return {0, 0, 0};
    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return {0, 0, 0};
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void random_scene(hittable_list &world) {

    material *ground_material = new lambertian(color(0.5, 0.5, 0.5));
    world.add(new sphere(point3(0,-1000,0), 1000, ground_material));

    for (int a = -3; a < 3; a++) {
        for (int b = -3; b < 3; b++) {
            double choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                material *sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    color albedo = color::random() * color::random();
                    sphere_material = new lambertian(albedo);
                    vec3 center2 = center + vec3(0, random_double(0, 0.5), 0);
                    world.add(new moving_sphere(
                            center, center2, 0.0, 1.0,
                            0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    color albedo = color::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = new metal(albedo, fuzz);
                    world.add(new sphere(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = new dielectric(1.5);
                    world.add(new sphere(center, 0.2, sphere_material));
                }
            }
        }
    }
}

void thread_work(int lines_per_thread, int t, int image_width, int image_height, int samples_per_pixel, int max_depth, camera &cam, hittable_list &world, std::vector<color> &pixels)
{
    int lineMax = (t + 1) * lines_per_thread - 1;
    int lineMin = t * lines_per_thread;
    for (int j = lineMin ; j <= lineMax ; ++j)
    {
        if (t == 0)
            std::cout << "[T " << t << "] Remaining " << lineMax - j << std::endl;
        for (int i = 0 ; i < image_width ; ++i)
        {
            color pixel_color(0, 0, 0);
            for (size_t s = 0 ; s < samples_per_pixel ; ++s)
            {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            int index = j * image_width + i;
            write_color(pixels[index], pixel_color, samples_per_pixel);
        }
    }
}

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 1280;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const size_t samples_per_pixel = 100;
    const size_t max_depth = 50;

    // World
    hittable_list world;

    random_scene(world);

    material *material3 = new metal(color(0.7, 0.6, 0.5), 0.0);
    world.add(new sphere(point3(0.0, 1.0, 0.5), 1.0, material3));
    material *ground_material = new metal(color(0.5, 0.5, 0.5), 0.1);
    world.add(new sphere(point3(0.0,-1000.0,0.0), 1000.0, ground_material));

    point3 lookfrom(13,4,3);
    point3 lookat(0,1,0.5);
    vec3 vup(0,1,0);
    double dist_to_focus = (lookfrom - lookat).length();
//    double dist_to_focus = 10.0;
    double aperture = 1.0;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    std::vector<color> pixels(image_height * image_width);
    int nb_threads = 6;
    int lines_per_thread = image_height / nb_threads;
    std::vector<std::thread> threads(nb_threads);

    for (int t = 0 ; t < nb_threads ; ++t)
    {
        threads[t] = std::thread(&thread_work, lines_per_thread, t, image_width, image_height, samples_per_pixel, max_depth, std::ref(cam), std::ref(world), std::ref(pixels));
    }

    for (int t = 0 ; t < nb_threads ; ++t)
    {
        std::cout << "thread " << t << " joined" << std::endl;
        threads[t].join();
    }

    std::cout << "writing to image" << std::endl;

    std::ofstream outfile ("./image.ppm");
    outfile << "P3\n" << std::to_string(image_width) << ' ' << std::to_string(image_height) << "\n255\n";
    for (int j = image_height - 1 ; j >= 0 ; --j)
    {
        for (int i = 0 ; i < image_width ; ++i)
        {
            color &pixel = pixels[j * image_width + i];
            outfile << pixel.x() << ' ' << pixel.y() << ' ' << pixel.z() << '\n';
        }
    }
    outfile.close();
    return 0;
}
