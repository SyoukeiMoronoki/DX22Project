struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
  float4 color : COLOR0;
};

texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float4x4 _WorldViewProj;
float4x4 _World;
float4 _Diffuse;
float4 _Ambient;

float _LightBrightness;
float4 _LightDiffuse;
float3 _LightPosition;
float3 _LightDirection;

float3 _ViewDirection;

bool _UseEar;

static const int GRID_COUNT = 16;
static const float GRID_WIDTH = 0.002f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;

  float4 offset = mul(v.vertex, _World);
  float3 vL = offset - _LightPosition;
  //true = 1.0f, false = -1.0f;
  float is_reverse = step(0.0f, -dot(_ViewDirection, _LightDirection));
  float3 normN = _LightDirection;
  float  lengthL = length(vL);
  float3 normL = normalize(vL);
  if (is_reverse == 1.0f)
  {
    normL.x *= -1.0f;
    normL.y *= -1.0f;
    normL.z *= -1.0f;
  }
  float  L = _LightBrightness * dot(normN, normL) / (lengthL * 0.5f);  // Œõ‚Ì‹­‚³
  L = max(L, 0.0f);
  o.color = _Diffuse * (_LightDiffuse * L + _Ambient * max(0.0f, 1.0f - L));
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  if (_UseEar)
  {
    i.uv.y += 0.5f;
    return tex2D(_MainTexSampler, i.uv);
  }
  return tex2D(_MainTexSampler, i.uv) * i.color;
}

technique Default
{
  pass
  {
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
