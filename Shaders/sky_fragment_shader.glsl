#version 330 core
out vec4 FragColor;

in vec2 fragment_uv;
in vec3 pos;
in vec3 star_pos;

uniform float timer;                // 在0 ~ 1之间
uniform float weatherFactor;        // 在0.5 ~ 1.0的范围
uniform sampler2D skyTexture;
uniform sampler2D cloudTexture1;
uniform sampler2D cloudTexture2;
uniform sampler2D nightTexture1;

// 返回的范围在0.05到0.95之间，白天的时候返回0.95
float clouds_color_factor()
{
    if (timer > 0.27 && timer < 0.79)           // 白天
        return 0.95;
    else if (timer < 0.21 || timer > 0.91)      // 黑夜
        return 0;
    else if (timer >= 0.21 && timer <= 0.27)    // 过渡
        return 0.95 * ((timer - 0.21) / 0.06);
    else                                        // 过渡
        return 0.95 * ((0.91 - timer) / 0.12);
}

float day_or_night()
{
    if (timer > 0.21 && timer < 0.91)
        return 0;
    else if (timer < 0.16 || timer > 0.96)
        return 1;
    else if (timer >= 0.16 && timer <= 0.21)    // 过渡
        return 1 * ((0.21 - timer) / 0.05);
    else                                        // 过渡
        return 1 * ((timer - 0.91) / 0.05);
}

// 基于简单哈希的噪声生成
float myHash(float n)
{
    return fract( (1.0 + sin(n)) * 415.92653);
}

float myNoise(vec3 x)
{
    float xhash = myHash(round(400*x.x) * 37.0);
    float yhash = myHash(round(400*x.y) * 57.0);
    float zhash = myHash(round(400*x.z) * 67.0);
    return fract(xhash + yhash + zhash);
}

void main()
{
    vec3 pos_norm = normalize(pos);
    // 天空的颜色
    vec2 sky_tex_uv = vec2(timer, fragment_uv.t);
    vec3 color = texture(skyTexture, sky_tex_uv).rgb;
    color = weatherFactor * color;
    // 计算云的贴图的坐标
    float cloud_tex_u = 0.5 + atan(pos_norm.z, pos_norm.x) / (2 * 3.14159265);
    float cloud_tex_v = 0.5 + asin(pos_norm.y) / 3.14159265;
    // 云的颜色，由天气和昼夜决定
    vec3 cloud_color = vec3(min(weatherFactor * 3.0 / 2.0, 1.0)) * clouds_color_factor();
    // 根据weatherFactor的值，(1.0 -> clouds1 (sunny), 0.5 -> clouds2 (rainy))
    float transparency = mix(texture(cloudTexture2, vec2(fract(cloud_tex_u + 0.1 * timer), cloud_tex_v)).r, texture(cloudTexture1, vec2(fract(cloud_tex_u + 0.1 * timer), cloud_tex_v)).r, (weatherFactor - 0.5) * 2.0);
    color = mix(color, cloud_color, clamp((2 - weatherFactor) * transparency, 0, 1));

    vec3 night_color = vec3(0.0f, 0.0f, 0.0f);
    float night_tex_u = 0.5 + atan(pos_norm.z, pos_norm.x) / (2 * 3.14159265);
    float night_tex_v = 2 * asin(pos_norm.y) / 3.14159265;
    if (pos_norm.y >= 0)
    {
        night_color = texture(nightTexture1, vec2(night_tex_u, night_tex_v)).rgb;
        // 加上星星的效果
        float threshold = 0.9999;
        float star_intensity = myNoise(normalize(star_pos));
        if (star_intensity >= threshold)
        {
            star_intensity = pow((star_intensity - threshold) / (1.0 - threshold), 10.0);
            //star_intensity = pow((star_intensity - threshold) / (1.0 - threshold), 6.0) * 0.8;
            night_color += vec3(star_intensity);
        }
    }

    color = mix(color, night_color, day_or_night());

    FragColor = vec4(color, 1.0);
}