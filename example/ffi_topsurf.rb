module FfiTopsurf
  extend FFI::Library
  ffi_lib "libtopsurf_x64d.so"

  # bool DLLAPI TopSurf_Initialize(int imagedim, int top);
  attach_function :TopSurf_Initialize, [:int, :int], :bool

end
