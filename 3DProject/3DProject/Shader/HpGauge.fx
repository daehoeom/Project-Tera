//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = "..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Disc.3ds";

float4x4 g_matViewProjection : ViewProjection;
float4x4 g_matWorld : World;


struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 UV : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 UV : TEXCOORD0;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.UV = Input.UV;
   Output.Position = mul( Input.Position, g_matWorld );
   Output.Position = mul( Output.Position, g_matViewProjection );
   
   return( Output );
   
}




texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\Program Files\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Earth.jpg";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};
float HpRatio = 0.6f;

struct PS_INPUT
{
   float2 UV : TEXCOORD0;
};

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{  
   if ( Input.UV.x > HpRatio )
   {
      return float4( 1.f, 1.f, 1.f, 0.f );
   }
   else
   {
      return tex2D( DiffuseSampler, Input.UV );
   }
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      ALPHABLENDENABLE = TRUE;
      BLENDOP = ADD;
      DESTBLEND = INVSRCALPHA;
      SRCBLEND = SRCALPHA;

      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

