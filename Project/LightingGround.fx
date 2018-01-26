struct appdata
{
  float4 vertex : POSITION;
  float3 normal : NORMAL0;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float4 vertex : SV_POSITION;
  float3 normal : NORMAL0;
  float2 uv : TEXCOORD0;
};

texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

texture _Normal;
sampler _NormalSampler = sampler_state
{
  Texture = _Normal;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float4x4 _WorldViewProj;
float4 _Diffuse;
float4 _Ambient;
float _Scale;

float _LightBrightness;
float4 _LightDiffuse;
float3 _LightPosition;
float3 _LightDirection;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  o.normal = v.normal;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float4 o = tex2D(_MainTexSampler, i.uv * _Scale * 0.1f) * _Diffuse;
  float2 vPos2 = (i.uv - float2(0.5f, 0.5f)) * _Scale;
  float3 vPos = float3(vPos2.x, 0.0f, vPos2.y);

  float3 vL = _LightPosition - vPos;
  float3 normal = i.normal + tex2D(_NormalSampler, i.uv * _Scale * 0.1f);
  float3 normND = normalize(_LightDirection * normal);
  float3 normL = normalize(vL);

  float lengthL = length(vL);
  float L = _LightBrightness * dot(normND, normL) / (lengthL * lengthL);
  L = max(L, 0.0f);
  o *= (L * _LightDiffuse + _Ambient * max(0.0f, 1.0f - L));
  return o;
}

technique Default
{
  pass
  {
    ZEnable = TRUE;               
    MultiSampleAntialias = TRUE;  
    CullMode = CCW;               
    ShadeMode = FLAT;          

    vertexshader = compile vs_3_0 vert();
    pixelshader = compile ps_3_0 frag();
  }
}
