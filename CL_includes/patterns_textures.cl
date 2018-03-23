
static float get_pattern2(t_ray *r, t_object *o)
{
    float scale;
    float scaleX;
    float scaleY;

    scale = (float)o->tex_scale;
    if (!scale)
        scale = 1.0;
    if (o->type == O_PLANE || o->type == O_DISK || o->type == O_TRIANGLE)
    {
        scaleX = scale * 25;
        scaleY = scale * 25;
    }
    else if (o->type == O_SPHERE)
    {
        scaleX = scale / 50;
        scaleY = scale / 50;
    }
    else if (o->type == O_CYL || o->type == O_PARABOLOID || o->type == O_CON)
    {
        scaleX = scale * 0.05;
        scaleY = scale * 10;
    }
	return (((sin(M_PI * r->tex[1] / scaleY)) > 0) ^ ((sin(M_PI * r->tex[0] / scaleX) > 0)));
}

static float get_pattern3(t_ray *r, t_object *o)
{
    float scale;
    float scaleX;
    float scaleY;

    scale = (float)o->tex_scale;
    if (!scale)
        scale = 1.0;
    if (o->type == O_PLANE || o->type == O_DISK || o->type == O_TRIANGLE)
    {
        scaleX = scale * 50;
        scaleY = scale * 50;
    }
    else if (o->type == O_SPHERE)
    {
        scaleX = scale / 25;
        scaleY = scale / 25;
    }
    else if (o->type == O_CYL || o->type == O_PARABOLOID || o->type == O_CON)
    {
        scaleX = scale * 0.1;
        scaleY = scale * 20;
    }
	return ((sin(M_PI * r->tex[0] / scaleX) > 0 ? sin(M_PI * r->tex[0] / scaleX) : -sin(M_PI * r->tex[0] / scaleX)));
}


static float get_pattern4(t_ray *r, t_object *o)
{
    float scale;
    float scaleX;
    float scaleY;

    scale = (float)o->tex_scale;
    if (!scale)
        scale = 1.0;
    if (o->type == O_PLANE || o->type == O_DISK || o->type == O_TRIANGLE)
    {
        scaleX = scale * 50;
        scaleY = scale * 50;
    }
    else if (o->type == O_SPHERE)
    {
        scaleX = scale / 25;
        scaleY = scale / 25;
    }
    else if (o->type == O_CYL || o->type == O_PARABOLOID || o->type == O_CON)
    {
        scaleX = scale * 0.1;
        scaleY = scale * 20;
    }
	return ((sin(M_PI * r->tex[1] / scaleY) > 0 ? sin(M_PI * r->tex[1] / scaleY) : -sin(M_PI * r->tex[1] / scaleY)));
}

static float get_pattern5(t_ray *r, t_object *o)
{
    float   scale;
    float   pattern;

    scale = (float)o->tex_scale;
    if (!scale)
        scale = 1.0;
    if (o->type == O_PLANE || o->type == O_DISK || o->type == O_TRIANGLE)
    {
        scale *= 0.015;
    }
    else if (o->type == O_SPHERE)
    {
        scale *= 50;
    }
    else if (o->type == O_CYL || o->type == O_PARABOLOID || o->type == O_CON)
    {
        scale *= 0.1;
    }
    pattern = sin(sqrt(r->tex[0] * r->tex[0] + r->tex[1] * r->tex[1]) * scale);
	return (pattern > 0 ? pattern : -pattern);
}

static float get_pattern6(t_ray *r, t_object *o) // , float x, float y
{
    float   scale;
    float   scaleX;
    float   scaleY;
    float   texX;
    float   texY;
    int     tx;
    int     ty;
    int     oddity;
    int     edge;

    scale = (float)o->tex_scale;
    if (!scale)
        scale = 1.0;
    if (o->type == O_PLANE || o->type == O_DISK || o->type == O_TRIANGLE)
    {
        scaleX = scale * 0.02;
        scaleY = scale * 0.02;
    }
    else if (o->type == O_SPHERE)
    {
        scaleX = scale * 15;
        scaleY = scale * 15;
    }
    else if (o->type == O_CYL || o->type == O_PARABOLOID || o->type == O_CON)
    {
        scaleX = 10;
        scaleY = 0.05;
    }
    texX =  r->tex[0] * scaleX;
    texY =  r->tex[1] * scaleY;
    tx = (int)(texX);
    ty = (int)(texY);
    oddity = (tx & 0x1) == (ty & 0x1);
    texX = texX - tx;
    texY = texY - ty;
    texX = texX < 0 ? -texX : texX;
    texY = texY < 0 ? -texY : texY;
    edge = ((texX < 0.1) && oddity) || (texY < 0.1);
	return (edge ? 0 : 1);
}

t_vector			get_object_color(t_object *o, t_ray *r, float x, float y)
{
    float pattern;

    pattern = 0;
    if (o->tex_id == T_CHECK)
	    pattern = get_pattern2(r, o);
    else if (o->tex_id == T_GRAD1)
        pattern = get_pattern3(r, o);
    else if (o->tex_id == T_GRAD2)
        pattern = get_pattern4(r, o);
    else if (o->tex_id == T_CIRC)
        pattern = get_pattern5(r, o);
    else if (o->tex_id == T_BRICK)
        pattern = get_pattern6(r, o);
    return (v_mult_d(o->color, 0.5 * pattern) + v_mult_d(o->color, 0.5));
}