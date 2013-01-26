#include<stdio.h>
#include<gegl.h>
#include<math.h>
int main(int argc , char **argv)
{
  GeglNode *load, *blur, *grey, *gegl,  *write;
  gdouble radius, std_dev;
  
  gegl_init (&argc, &argv);

  if(argv[1]==NULL || argv[2]==NULL)
    {
       g_print ("\nGrey-Blur using GEGL Operations.");
       g_print ("\nUsage: %s <input-image> <output-image>\n", argv[0]);
       return 1;
    }
  
  gegl = gegl_node_new ();
  
  load = gegl_node_new_child (gegl,
                             "operation", "gegl:load",
                             "path", argv[1],
                             NULL);
 
  grey = gegl_node_new_child (gegl,
                             "operation", "gegl:grey",
                             NULL);
  
  g_print ("\nEnter the Radius: ");
  scanf ("%lf", &radius);
  radius   = fabs (radius) + 1.0;
  std_dev = sqrt (-(radius * radius) / (2 * log (1.0 / 255.0)));

  blur = gegl_node_new_child (gegl,
                              "operation", "gegl:gaussian-blur",
                              "std_dev_x", std_dev,
                              "std_dev_y", std_dev,
                              NULL);
  write = gegl_node_new_child (gegl,
                              "operation", "gegl:save",
                              "path", argv[2],
                              NULL);
  gegl_node_link_many (load, grey, blur, write, NULL);
  gegl_node_process (write);
  

  g_object_unref (gegl);
  
  gegl_exit();
  return 0;
}
                              
