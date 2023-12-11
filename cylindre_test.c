// void	ft_intersect_ray_cylinder(t_shape *sh, t_ray *ray)
// {
// 	t_mat	tmp;
// 	t_argb	dot;
// 	t_pt	calc;
// 	t_argb	dist;
// 	int		ret;

// 	ft_cylinder_calc_one(sh, ray, &tmp, &dot);
// 	ft_cylinder_calc_two(&calc, ray, &tmp, &dot);
// 	if ((ret = ft_cylinder_calc_three(&calc, &dist, &dot, ray)) != 0)
// 		return ;
// 	if ((ret = ft_cylinder_calc_five(sh, &dist, &dot, ray)) != 0)
// 		return ;
// 	if ((fabs(calc.y + calc.x * dist.r)) < dist.a \
// 		&& (ray->lenght = dist.r + 0.001))
// 	{
// 		if (ft_dot_product(ray->dir, sh->n) > 0)
// 			ft_inv_norm(&sh->n);
// 		return ;
// 	}
// 	ray->lenght = -1;
// }




#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y, z;
} Vector;

typedef struct {
    Vector origin;
    Vector direction;
} Ray;

typedef struct {
    Vector A0;  // Point sur l'axe du cylindre
    Vector Adir;  // Vecteur unitaire indiquant la direction de l'axe
    float r;  // Rayon du cylindre
    float h;  // Hauteur du cylindre
} Cylinder;

// Fonction pour normaliser un vecteur
Vector normalize(Vector v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vector){v.x / length, v.y / length, v.z / length};
}

// Fonction pour calculer le produit vectoriel de deux vecteurs
Vector crossProduct(Vector v1, Vector v2) {
    return (Vector){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

// Fonction pour trouver l'intersection entre un rayon et un cylindre
int intersectRayCylinder(Ray ray, Cylinder cylinder, float *t1, float *t2) {
    // Calcul de U et V (vecteurs orthogonaux à Adir)
    Vector U = normalize(crossProduct(cylinder.Adir, (Vector){1, 0, 0}));
    Vector V = crossProduct(cylinder.Adir, U);

    // Paramètres de l'équation quadratique
    float a = U.x * U.x + V.x * V.x;
    float b = 2 * (U.x * (ray.direction.x - cylinder.Adir.x * dot(ray.direction, cylinder.Adir)) + V.x * (ray.direction.y - cylinder.Adir.y * dot(ray.direction, cylinder.Adir)));
    float c = (ray.direction.x - cylinder.Adir.x * dot(ray.direction, cylinder.Adir)) * (ray.direction.x - cylinder.Adir.x * dot(ray.direction, cylinder.Adir)) +
              (ray.direction.y - cylinder.Adir.y * dot(ray.direction, cylinder.Adir)) * (ray.direction.y - cylinder.Adir.y * dot(ray.direction, cylinder.Adir)) -
              cylinder.r * cylinder.r * (U.x * U.x + V.x * V.x);

    // Discriminant de l'équation quadratique
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        // Pas d'intersection
        return 0;
    } else {
        // Calcul des solutions de l'équation quadratique
        *t1 = (-b - sqrt(discriminant)) / (2 * a);
        *t2 = (-b + sqrt(discriminant)) / (2 * a);

        // Vérifier que les solutions sont positives et dans la hauteur du cylindre
        if (*t1 >= 0 && *t1 <= cylinder.h && *t2 >= 0 && *t2 <= cylinder.h) {
            return 1;  // Intersection trouvée
        } else {
            return 0;  // Pas d'intersection dans la hauteur du cylindre
        }
    }
}

int main() {
    // Définir le rayon
    Ray ray = {{0, 0, 0}, {1, 1, 1}};  // Origine et direction du rayon

    // Définir le cylindre
    Cylinder cylinder = {{0, 0, 0}, {0, 1, 0}, 1.0, 2.0};  // A0, Adir, Rayon, Hauteur

    // Variables pour stocker les points d'intersection
    float t1, t2;

    // Vérifier l'intersection
    if (intersectRayCylinder(ray, cylinder, &t1, &t2)) {
        printf("Intersection trouvée aux paramètres t1 = %f et t2 = %f\n", t1, t2);
    } else {
        printf("Pas d'intersection\n");
    }

    return 0;
}
