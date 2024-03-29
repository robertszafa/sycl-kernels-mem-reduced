-- velfg_superkernel
module ASTInstance ( ast
        , functionSignaturesList
        , stencilDefinitionsList
        , mainArgDeclsList 
        , scalarisedArgsList
        , origNamesList
        , superkernelName
        ) where
import TyTraCLAST

superkernelName :: String
superkernelName = "velfg_superkernel"

ast :: TyTraCLAST
ast = [
        -- velfg_map_76
       (Vec VS (SVec 4 (Scalar VDC DFloat "w_s_0" )) , Stencil (SVec 4 (Scalar VDC DInt "s1")) (Vec VI (Scalar VDC DFloat "w_0")))
       ,(Vec VS (SVec 5 (Scalar VDC DFloat "v_s_0" )) , Stencil (SVec 5 (Scalar VDC DInt "s2")) (Vec VI (Scalar VDC DFloat "v_0")))
       ,(Vec VS (SVec 5 (Scalar VDC DFloat "u_s_0" )) , Stencil (SVec 5 (Scalar VDC DInt "s3")) (Vec VI (Scalar VDC DFloat "u_0")))
       ,( (Tuple [Vec VT (Scalar VDC DFloat "cov1_1"),Vec VT (Scalar VDC DFloat "cov2_1"),Vec VT (Scalar VDC DFloat "cov3_1"),Vec VT (Scalar VDC DFloat "cov4_1"),Vec VT (Scalar VDC DFloat "cov5_1"),Vec VT (Scalar VDC DFloat "cov6_1"),Vec VT (Scalar VDC DFloat "cov9_1"),Vec VT (Scalar VDC DFloat "diu1_1"),Vec VT (Scalar VDC DFloat "diu2_1"),Vec VT (Scalar VDC DFloat "diu3_1"),Vec VT (Scalar VDC DFloat "diu4_1"),Vec VT (Scalar VDC DFloat "diu5_1"),Vec VT (Scalar VDC DFloat "diu6_1"),Vec VT (Scalar VDC DFloat "diu9_1"),Vec VT (Scalar VDC DFloat "nou1_1"),Vec VT (Scalar VDC DFloat "nou2_1"),Vec VT (Scalar VDC DFloat "nou3_1"),Vec VT (Scalar VDC DFloat "nou4_1"),Vec VT (Scalar VDC DFloat "nou5_1"),Vec VT (Scalar VDC DFloat "nou6_1"),Vec VT (Scalar VDC DFloat "nou9_1")]), UnzipT ( Map (Function "velfg_map_76"  [FVec [(-1,601)] (Scalar VDC DFloat "dx1_0"),FVec [(0,601)] (Scalar VDC DFloat "dy1_0"),FVec [(-1,92)] (Scalar VDC DFloat "dzn_0"),FVec [(-1,92)] (Scalar VDC DFloat "dzs_0")]) (ZipT [Vec VS (SVec 5 (Scalar VDC DFloat "u_s_0")),Vec VS (SVec 5 (Scalar VDC DFloat "v_s_0")),Vec VS (SVec 4 (Scalar VDC DFloat "w_s_0"))]) ) )
        -- velfg_map_133
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "v_s_1" )) , Stencil (SVec 2 (Scalar VDC DInt "s4")) (Vec VI (Scalar VDC DFloat "v_0")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "u_s_1" )) , Stencil (SVec 2 (Scalar VDC DInt "s5")) (Vec VI (Scalar VDC DFloat "u_0")))
       ,(Vec VS (SVec 3 (Scalar VDC DFloat "w_s_1" )) , Stencil (SVec 3 (Scalar VDC DInt "s6")) (Vec VI (Scalar VDC DFloat "w_0")))
       ,( (Tuple [Vec VT (Scalar VDC DFloat "cov7_1"),Vec VT (Scalar VDC DFloat "cov8_1"),Vec VT (Scalar VDC DFloat "diu7_1"),Vec VT (Scalar VDC DFloat "diu8_1"),Vec VT (Scalar VDC DFloat "nou7_1"),Vec VT (Scalar VDC DFloat "nou8_1")]), UnzipT ( Map (Function "velfg_map_133"  [FVec [(-1,92)] (Scalar VDC DFloat "dzn_0"),FVec [(-1,601)] (Scalar VDC DFloat "dx1_0"),FVec [(0,601)] (Scalar VDC DFloat "dy1_0")]) (ZipT [Vec VS (SVec 2 (Scalar VDC DFloat "u_s_1")),Vec VS (SVec 3 (Scalar VDC DFloat "w_s_1")),Vec VS (SVec 2 (Scalar VDC DFloat "v_s_1"))]) ) )
        -- velfg_map_218
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov7_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s7")) (Vec VT (Scalar VDC DFloat "cov7_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu7_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s7")) (Vec VT (Scalar VDC DFloat "diu7_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov9_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s9")) (Vec VT (Scalar VDC DFloat "cov9_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu5_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s10")) (Vec VT (Scalar VDC DFloat "diu5_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu9_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s9")) (Vec VT (Scalar VDC DFloat "diu9_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov5_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s10")) (Vec VT (Scalar VDC DFloat "cov5_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu2_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s13")) (Vec VT (Scalar VDC DFloat "diu2_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu8_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s13")) (Vec VT (Scalar VDC DFloat "diu8_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov2_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s13")) (Vec VT (Scalar VDC DFloat "cov2_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov8_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s13")) (Vec VT (Scalar VDC DFloat "cov8_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov1_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s17")) (Vec VT (Scalar VDC DFloat "cov1_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov4_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s7")) (Vec VT (Scalar VDC DFloat "cov4_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu1_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s17")) (Vec VT (Scalar VDC DFloat "diu1_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu4_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s7")) (Vec VT (Scalar VDC DFloat "diu4_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov6_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s9")) (Vec VT (Scalar VDC DFloat "cov6_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu6_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s9")) (Vec VT (Scalar VDC DFloat "diu6_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "cov3_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s9")) (Vec VT (Scalar VDC DFloat "cov3_1")))
       ,(Vec VS (SVec 2 (Scalar VDC DFloat "diu3_s_0" )) , Stencil (SVec 2 (Scalar VDC DInt "s9")) (Vec VT (Scalar VDC DFloat "diu3_1")))
       ,( (Tuple [Vec VT (Scalar VDC DFloat "dfu1_1"),Vec VT (Scalar VDC DFloat "dfv1_1"),Vec VT (Scalar VDC DFloat "dfw1_1"),Vec VO (Scalar VDC DFloat "f_1"),Vec VO (Scalar VDC DFloat "g_1"),Vec VO (Scalar VDC DFloat "h_1")]), UnzipT ( Map (Function "velfg_map_218"  [FVec [(-1,601)] (Scalar VDC DFloat "dx1_0"),FVec [(0,601)] (Scalar VDC DFloat "dy1_0"),FVec [(-1,92)] (Scalar VDC DFloat "dzn_0"),FVec [(-1,92)] (Scalar VDC DFloat "dzs_0")]) (ZipT [Vec VS (SVec 2 (Scalar VDC DFloat "cov1_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov2_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov3_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu1_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu2_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu3_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov4_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov5_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov6_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu4_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu5_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu6_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov7_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov8_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "cov9_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu7_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu8_s_0")),Vec VS (SVec 2 (Scalar VDC DFloat "diu9_s_0"))]) ) )
        ]

functionSignaturesList = [
        ("velfg_map_133",  [Tuple [FVec [(-1,92)] (Scalar VI DFloat "dzn_0"),FVec [(-1,601)] (Scalar VI DFloat "dx1_0"),FVec [(0,601)] (Scalar VI DFloat "dy1_0")],Tuple [SVec 2 (Scalar VDC DFloat "u_s_1"),SVec 3 (Scalar VDC DFloat "w_s_1"),SVec 2 (Scalar VDC DFloat "v_s_1")],Tuple [Scalar VT DFloat "cov7_1",Scalar VT DFloat "cov8_1",Scalar VT DFloat "diu7_1",Scalar VT DFloat "diu8_1",Scalar VT DFloat "nou7_1",Scalar VT DFloat "nou8_1"]]),
        ("velfg_map_218",  [Tuple [FVec [(-1,601)] (Scalar VI DFloat "dx1_0"),FVec [(0,601)] (Scalar VI DFloat "dy1_0"),FVec [(-1,92)] (Scalar VI DFloat "dzn_0"),FVec [(-1,92)] (Scalar VI DFloat "dzs_0")],Tuple [SVec 2 (Scalar VDC DFloat "cov1_s_0"),SVec 2 (Scalar VDC DFloat "cov2_s_0"),SVec 2 (Scalar VDC DFloat "cov3_s_0"),SVec 2 (Scalar VDC DFloat "diu1_s_0"),SVec 2 (Scalar VDC DFloat "diu2_s_0"),SVec 2 (Scalar VDC DFloat "diu3_s_0"),SVec 2 (Scalar VDC DFloat "cov4_s_0"),SVec 2 (Scalar VDC DFloat "cov5_s_0"),SVec 2 (Scalar VDC DFloat "cov6_s_0"),SVec 2 (Scalar VDC DFloat "diu4_s_0"),SVec 2 (Scalar VDC DFloat "diu5_s_0"),SVec 2 (Scalar VDC DFloat "diu6_s_0"),SVec 2 (Scalar VDC DFloat "cov7_s_0"),SVec 2 (Scalar VDC DFloat "cov8_s_0"),SVec 2 (Scalar VDC DFloat "cov9_s_0"),SVec 2 (Scalar VDC DFloat "diu7_s_0"),SVec 2 (Scalar VDC DFloat "diu8_s_0"),SVec 2 (Scalar VDC DFloat "diu9_s_0")],Tuple [Scalar VT DFloat "dfu1_1",Scalar VT DFloat "dfv1_1",Scalar VT DFloat "dfw1_1",Scalar VO DFloat "f_1",Scalar VO DFloat "g_1",Scalar VO DFloat "h_1"]]),
        ("velfg_map_76",  [Tuple [FVec [(-1,601)] (Scalar VI DFloat "dx1_0"),FVec [(0,601)] (Scalar VI DFloat "dy1_0"),FVec [(-1,92)] (Scalar VI DFloat "dzn_0"),FVec [(-1,92)] (Scalar VI DFloat "dzs_0")],Tuple [SVec 5 (Scalar VDC DFloat "u_s_0"),SVec 5 (Scalar VDC DFloat "v_s_0"),SVec 4 (Scalar VDC DFloat "w_s_0")],Tuple [Scalar VT DFloat "cov1_1",Scalar VT DFloat "cov2_1",Scalar VT DFloat "cov3_1",Scalar VT DFloat "cov4_1",Scalar VT DFloat "cov5_1",Scalar VT DFloat "cov6_1",Scalar VT DFloat "cov9_1",Scalar VT DFloat "diu1_1",Scalar VT DFloat "diu2_1",Scalar VT DFloat "diu3_1",Scalar VT DFloat "diu4_1",Scalar VT DFloat "diu5_1",Scalar VT DFloat "diu6_1",Scalar VT DFloat "diu9_1",Scalar VT DFloat "nou1_1",Scalar VT DFloat "nou2_1",Scalar VT DFloat "nou3_1",Scalar VT DFloat "nou4_1",Scalar VT DFloat "nou5_1",Scalar VT DFloat "nou6_1",Scalar VT DFloat "nou9_1"]])
    ]
stencilDefinitionsList = [("s1" , [603,604,1205,363007] ), ("s2" , [603,362405,362406,363006,363007] ), ("s3" , [603,362405,363006,363007,363608] ), ("s4" , [362405,724809] ), ("s5" , [363006,725410] ), ("s6" , [362405,363006,363007] ), ("s7" , [364213,364214] ), ("s9" , [364213,727822] ), ("s10" , [364818,365422] ), ("s13" , [364213,364816] ), ("s17" , [364818,364819] )]

mainArgDeclsList = [
      ("w_0" , MkFDecl "real"  (Just [(1,33341168)]) (Just In) ["w_0"] )
    , ("u_0" , MkFDecl "real"  (Just [(1,33341168)]) (Just In) ["u_0"] )
    , ("dx1_0" , MkFDecl "real"  (Just [(-1,601)]) (Just In) ["dx1_0"] )
    , ("dy1_0" , MkFDecl "real"  (Just [(0,601)]) (Just In) ["dy1_0"] )
    , ("v_0" , MkFDecl "real"  (Just [(1,33341168)]) (Just In) ["v_0"] )
    , ("dzs_0" , MkFDecl "real"  (Just [(-1,92)]) (Just In) ["dzs_0"] )
    , ("dzn_0" , MkFDecl "real"  (Just [(-1,92)]) (Just In) ["dzn_0"] )
    , ("f_1" , MkFDecl "real"  (Just [(1,32869291)]) (Just Out) ["f_1"] )
    , ("h_1" , MkFDecl "real"  (Just [(1,32869291)]) (Just Out) ["h_1"] )
    , ("g_1" , MkFDecl "real"  (Just [(1,32869291)]) (Just Out) ["g_1"] )
  ]

scalarisedArgsList = [
     ( "velfg_map_133",[("dzn",(0,In,"real")), ("u",(1,In,"real")), ("u",(2,In,"real")), ("w",(1,In,"real")), ("w",(2,In,"real")), ("w",(3,In,"real")), ("dx1",(0,In,"real")), ("nou7",(0,InOut,"real")), ("diu7",(0,InOut,"real")), ("v",(1,In,"real")), ("v",(2,In,"real")), ("dy1",(0,In,"real")), ("nou8",(0,InOut,"real")), ("diu8",(0,InOut,"real")), ("cov7",(0,Out,"real")), ("cov8",(0,Out,"real"))])
    ,( "velfg_map_218",[("dx1",(0,In,"real")), ("cov1",(1,In,"real")), ("cov1",(2,In,"real")), ("cov2",(1,In,"real")), ("cov2",(2,In,"real")), ("cov3",(1,In,"real")), ("cov3",(2,In,"real")), ("diu1",(1,In,"real")), ("diu1",(2,In,"real")), ("diu2",(1,In,"real")), ("diu2",(2,In,"real")), ("dy1",(0,In,"real")), ("diu3",(1,In,"real")), ("diu3",(2,In,"real")), ("dzn",(0,In,"real")), ("dfu1",(0,InOut,"real")), ("cov4",(1,In,"real")), ("cov4",(2,In,"real")), ("cov5",(1,In,"real")), ("cov5",(2,In,"real")), ("cov6",(1,In,"real")), ("cov6",(2,In,"real")), ("diu4",(1,In,"real")), ("diu4",(2,In,"real")), ("diu5",(1,In,"real")), ("diu5",(2,In,"real")), ("diu6",(1,In,"real")), ("diu6",(2,In,"real")), ("dfv1",(0,InOut,"real")), ("cov7",(1,In,"real")), ("cov7",(2,In,"real")), ("cov8",(1,In,"real")), ("cov8",(2,In,"real")), ("cov9",(1,In,"real")), ("cov9",(2,In,"real")), ("diu7",(1,In,"real")), ("diu7",(2,In,"real")), ("diu8",(1,In,"real")), ("diu8",(2,In,"real")), ("diu9",(1,In,"real")), ("diu9",(2,In,"real")), ("dzs",(0,In,"real")), ("dfw1",(0,InOut,"real")), ("f",(0,Out,"real")), ("g",(0,Out,"real")), ("h",(0,Out,"real"))])
    ,( "velfg_map_76",[("u",(1,In,"real")), ("u",(2,In,"real")), ("u",(3,In,"real")), ("u",(4,In,"real")), ("u",(5,In,"real")), ("dx1",(0,In,"real")), ("v",(1,In,"real")), ("v",(2,In,"real")), ("v",(3,In,"real")), ("v",(4,In,"real")), ("v",(5,In,"real")), ("dy1",(0,In,"real")), ("w",(1,In,"real")), ("w",(2,In,"real")), ("w",(3,In,"real")), ("w",(4,In,"real")), ("dzn",(0,In,"real")), ("nou1",(0,InOut,"real")), ("diu1",(0,InOut,"real")), ("nou5",(0,InOut,"real")), ("diu5",(0,InOut,"real")), ("nou9",(0,InOut,"real")), ("diu9",(0,InOut,"real")), ("nou2",(0,InOut,"real")), ("diu2",(0,InOut,"real")), ("dzs",(0,In,"real")), ("nou3",(0,InOut,"real")), ("diu3",(0,InOut,"real")), ("nou4",(0,InOut,"real")), ("diu4",(0,InOut,"real")), ("nou6",(0,InOut,"real")), ("diu6",(0,InOut,"real")), ("cov1",(0,Out,"real")), ("cov5",(0,Out,"real")), ("cov9",(0,Out,"real")), ("cov2",(0,Out,"real")), ("cov3",(0,Out,"real")), ("cov4",(0,Out,"real")), ("cov6",(0,Out,"real"))])
  ]

origNamesList = [
     ( "velfg_map_76",[("dx1",[("dx1_0",In)]), ("dy1",[("dy1_0",In)]), ("dzn",[("dzn_0",In)]), ("dzs",[("dzs_0",In)]), ("u",[("u_s_0",In)]), ("v",[("v_s_0",In)]), ("w",[("w_s_0",In)]), ("cov1",[("cov1_1",Out)]), ("cov2",[("cov2_1",Out)]), ("cov3",[("cov3_1",Out)]), ("cov4",[("cov4_1",Out)]), ("cov5",[("cov5_1",Out)]), ("cov6",[("cov6_1",Out)]), ("cov9",[("cov9_1",Out)]), ("diu1",[("diu1_1",Out)]), ("diu2",[("diu2_1",Out)]), ("diu3",[("diu3_1",Out)]), ("diu4",[("diu4_1",Out)]), ("diu5",[("diu5_1",Out)]), ("diu6",[("diu6_1",Out)]), ("diu9",[("diu9_1",Out)]), ("nou1",[("nou1_1",Out)]), ("nou2",[("nou2_1",Out)]), ("nou3",[("nou3_1",Out)]), ("nou4",[("nou4_1",Out)]), ("nou5",[("nou5_1",Out)]), ("nou6",[("nou6_1",Out)]), ("nou9",[("nou9_1",Out)])])
    ,( "velfg_map_133",[("dzn",[("dzn_0",In)]), ("dx1",[("dx1_0",In)]), ("dy1",[("dy1_0",In)]), ("u",[("u_s_1",In)]), ("w",[("w_s_1",In)]), ("v",[("v_s_1",In)]), ("cov7",[("cov7_1",Out)]), ("cov8",[("cov8_1",Out)]), ("diu7",[("diu7_1",Out)]), ("diu8",[("diu8_1",Out)]), ("nou7",[("nou7_1",Out)]), ("nou8",[("nou8_1",Out)])])
    ,( "velfg_map_218",[("dx1",[("dx1_0",In)]), ("dy1",[("dy1_0",In)]), ("dzn",[("dzn_0",In)]), ("dzs",[("dzs_0",In)]), ("cov1",[("cov1_s_0",In)]), ("cov2",[("cov2_s_0",In)]), ("cov3",[("cov3_s_0",In)]), ("diu1",[("diu1_s_0",In)]), ("diu2",[("diu2_s_0",In)]), ("diu3",[("diu3_s_0",In)]), ("cov4",[("cov4_s_0",In)]), ("cov5",[("cov5_s_0",In)]), ("cov6",[("cov6_s_0",In)]), ("diu4",[("diu4_s_0",In)]), ("diu5",[("diu5_s_0",In)]), ("diu6",[("diu6_s_0",In)]), ("cov7",[("cov7_s_0",In)]), ("cov8",[("cov8_s_0",In)]), ("cov9",[("cov9_s_0",In)]), ("diu7",[("diu7_s_0",In)]), ("diu8",[("diu8_s_0",In)]), ("diu9",[("diu9_s_0",In)]), ("dfu1",[("dfu1_1",Out)]), ("dfv1",[("dfv1_1",Out)]), ("dfw1",[("dfw1_1",Out)]), ("f",[("f_1",Out)]), ("g",[("g_1",Out)]), ("h",[("h_1",Out)])])
  ]

{-
w_0 :: Vec 33341168 Float
v_0 :: Vec 33341168 Float
u_0 :: Vec 33341168 Float
dx1_0 :: FVec [(-1,601)] Float
dy1_0 :: FVec [(0,601)] Float
dzn_0 :: FVec [(-1,92)] Float
dzs_0 :: FVec [(-1,92)] Float

f_1 :: Vec 32869291 Float
g_1 :: Vec 32869291 Float
h_1 :: Vec 32869291 Float

velfg_map_76 :: (Float,Float,Float,Float) -> (SVec 5 Float,SVec 5 Float,SVec 4 Float) -> (Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float,Float)
velfg_map_218 :: (Float,Float,Float,Float) -> (SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float,SVec 2 Float) -> (Float,Float,Float,Float,Float,Float)
velfg_map_133 :: (Float,Float,Float) -> (SVec 2 Float,SVec 3 Float,SVec 2 Float) -> (Float,Float,Float,Float,Float,Float)

main :: (Vec 33341168 Float,Vec 33341168 Float,Vec 33341168 Float,FVec [(-1,601)] Float,FVec [(0,601)] Float,FVec [(-1,92)] Float,FVec [(-1,92)] Float) -> (Vec 32869291 Float,Vec 32869291 Float,Vec 32869291 Float)
main (w_0,v_0,u_0,dx1_0,dy1_0,dzn_0,dzs_0) =
  let
     -- velfg_map_76
    s1 = [603,604,1205,363007]
    w_s_0 = stencil s1 w_0
    s2 = [603,362405,362406,363006,363007]
    v_s_0 = stencil s2 v_0
    s3 = [603,362405,363006,363007,363608]
    u_s_0 = stencil s3 u_0
    (cov1_1,cov2_1,cov3_1,cov4_1,cov5_1,cov6_1,cov9_1,diu1_1,diu2_1,diu3_1,diu4_1,diu5_1,diu6_1,diu9_1,nou1_1,nou2_1,nou3_1,nou4_1,nou5_1,nou6_1,nou9_1) = unzipt $ map (velfg_map_76 (dx1_0,dy1_0,dzn_0,dzs_0)) (zipt (u_s_0,v_s_0,w_s_0))
     -- velfg_map_133
    s4 = [362405,724809]
    v_s_1 = stencil s4 v_0
    s5 = [363006,725410]
    u_s_1 = stencil s5 u_0
    s6 = [362405,363006,363007]
    w_s_1 = stencil s6 w_0
    (cov7_1,cov8_1,diu7_1,diu8_1,nou7_1,nou8_1) = unzipt $ map (velfg_map_133 (dzn_0,dx1_0,dy1_0)) (zipt (u_s_1,w_s_1,v_s_1))
     -- velfg_map_218
    s7 = [364213,364214]
    cov7_s_0 = stencil s7 cov7_1
    s8 = [364213,364214]
    diu7_s_0 = stencil s8 diu7_1
    s9 = [364213,727822]
    cov9_s_0 = stencil s9 cov9_1
    s10 = [364818,365422]
    diu5_s_0 = stencil s10 diu5_1
    s11 = [364213,727822]
    diu9_s_0 = stencil s11 diu9_1
    s12 = [364818,365422]
    cov5_s_0 = stencil s12 cov5_1
    s13 = [364213,364816]
    diu2_s_0 = stencil s13 diu2_1
    s14 = [364213,364816]
    diu8_s_0 = stencil s14 diu8_1
    s15 = [364213,364816]
    cov2_s_0 = stencil s15 cov2_1
    s16 = [364213,364816]
    cov8_s_0 = stencil s16 cov8_1
    s17 = [364818,364819]
    cov1_s_0 = stencil s17 cov1_1
    s18 = [364213,364214]
    cov4_s_0 = stencil s18 cov4_1
    s19 = [364818,364819]
    diu1_s_0 = stencil s19 diu1_1
    s20 = [364213,364214]
    diu4_s_0 = stencil s20 diu4_1
    s21 = [364213,727822]
    cov6_s_0 = stencil s21 cov6_1
    s22 = [364213,727822]
    diu6_s_0 = stencil s22 diu6_1
    s23 = [364213,727822]
    cov3_s_0 = stencil s23 cov3_1
    s24 = [364213,727822]
    diu3_s_0 = stencil s24 diu3_1
    (dfu1_1,dfv1_1,dfw1_1,f_1,g_1,h_1) = unzipt $ map (velfg_map_218 (dx1_0,dy1_0,dzn_0,dzs_0)) (zipt (cov1_s_0,cov2_s_0,cov3_s_0,diu1_s_0,diu2_s_0,diu3_s_0,cov4_s_0,cov5_s_0,cov6_s_0,diu4_s_0,diu5_s_0,diu6_s_0,cov7_s_0,cov8_s_0,cov9_s_0,diu7_s_0,diu8_s_0,diu9_s_0))
  in
    (f_1,g_1,h_1)
-}
