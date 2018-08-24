using System;
using System.Collections.Generic;
using System.Drawing;

using OpenTK.Graphics.OpenGL;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Drawing.Imaging;

namespace ImpsEngine
{
    public class IABitmap
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate Bitmap CreateRefFromAssetDelegate(string assetName);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate Bitmap CreateRefFromScreenDelegate(int x, int y, int width, int height);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IASize GetSourceSizeDelegate(Bitmap bitmapRef);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void BindDelegate(Bitmap bitmapRef);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void DestroyBitmapRefDelegate(Bitmap bitmapRef);

        private static HashSet<Bitmap> bitmaps = new HashSet<Bitmap>();

        public static string AssetFolder = @"..\Assets\";

        private static Bitmap CreateRefFromAsset(String assetName)
        {
            var bitmap = new Bitmap(AssetFolder + assetName);
            Debug.Assert(bitmap.PixelFormat == System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            BitmapData data = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height),
                ImageLockMode.ReadWrite, bitmap.PixelFormat);

            IntPtr ptr = data.Scan0;

            // Declare an array to hold the bytes of the bitmap.
            int numBytes = Math.Abs(data.Stride) * bitmap.Height;
            Debug.Assert(numBytes == bitmap.Height * bitmap.Width * 4);
            byte[] rgbaValues = new byte[numBytes];

            Marshal.Copy(ptr, rgbaValues, 0, numBytes);

            for (int counter = 0; counter < rgbaValues.Length; counter += 4)
            {
                rgbaValues[counter] = Convert.ToByte(rgbaValues[counter] * rgbaValues[counter + 3] / 255.0f);
                rgbaValues[counter + 1] = Convert.ToByte(rgbaValues[counter + 1] * rgbaValues[counter + 3] / 255.0f);
                rgbaValues[counter + 2] = Convert.ToByte(rgbaValues[counter + 2] * rgbaValues[counter + 3] / 255.0f);
            }

            Marshal.Copy(rgbaValues, 0, ptr, numBytes);

            bitmap.UnlockBits(data);
            bitmaps.Add(bitmap);
            return bitmap;
        }

        public static void AddBitmapRef(Bitmap bitmap)
        {
            bitmaps.Add(bitmap);
        }

        private static IASize GetSourceSize(Bitmap bitmap)
        {
            IASize size = new IASize();
            size.width = bitmap.Width;
            size.height = bitmap.Height;
            return size;
        }

        private static void Bind(Bitmap bitmap)
        {
            BitmapData data = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.ReadOnly, bitmap.PixelFormat);
            switch (bitmap.PixelFormat)
            {
                case System.Drawing.Imaging.PixelFormat.Format32bppArgb:
                case System.Drawing.Imaging.PixelFormat.Format32bppRgb:
                    GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, data.Width, data.Height, 0,
                OpenTK.Graphics.OpenGL.PixelFormat.Bgra, PixelType.UnsignedByte, data.Scan0);
                    break;
                case System.Drawing.Imaging.PixelFormat.Format24bppRgb:
                    GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgb, data.Width, data.Height, 0,
                    OpenTK.Graphics.OpenGL.PixelFormat.Bgr, PixelType.UnsignedByte, data.Scan0);
                    break;
                default:
                    throw new NotImplementedException();
            }
            bitmap.UnlockBits(data);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMagFilter.Linear);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapS, (int)TextureWrapMode.Repeat);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureWrapT, (int)TextureWrapMode.Repeat);

        }
        private static void DestroyBitmapRef(Bitmap bitmap)
        {
            bitmaps.Remove(bitmap);
        }

        public static IABitmapMappings GetBitmapMappings()
        {
            IABitmapMappings mappings = new IABitmapMappings();
            mappings.createRefFromAsset = new CreateRefFromAssetDelegate(CreateRefFromAsset);
            mappings.getSourceSize = new GetSourceSizeDelegate(GetSourceSize);
            mappings.bind = new BindDelegate(Bind);
            mappings.destroyBitmapRef = new DestroyBitmapRefDelegate(DestroyBitmapRef);
            return mappings;
        }

        [StructLayout(LayoutKind.Sequential), Serializable]
        public struct IABitmapMappings
        {
            public CreateRefFromAssetDelegate createRefFromAsset;
            public CreateRefFromScreenDelegate createRefFromScreen;
            public GetSourceSizeDelegate getSourceSize;
            public BindDelegate bind;
            public DestroyBitmapRefDelegate destroyBitmapRef;
        }

        [StructLayout(LayoutKind.Sequential), Serializable]
        public struct IASize
        {
            public float width;
            public float height;
        }
    }
}
