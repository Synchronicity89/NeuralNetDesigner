using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NeuralNetDesignerLib
{
    public static class ObjectExtensions
    {
        //An extension method give meaningful string representation of an object by using reflection to get the names and values of its properties
        public static string ToMeaningfulString(this object obj, int depth = 0)
        {
            if (obj == null)
            {
                return "null";
            }

            string output = "";
            if(depth == 0)
                output += obj.GetType().Name + " {";
            // if the type is an enum or simple type like int, just return the name of the enum or the value of the simple type
            if (obj.GetType().IsEnum)
            {
                output += obj.ToString();
                return output;
            }
            // All simple types are value types, so we can check for value type and return the value
            if(obj.GetType().IsValueType)
            {
                output += obj.ToString();
                return output;
            }

            System.Reflection.PropertyInfo[] properties = obj.GetType().GetProperties();
            foreach (System.Reflection.PropertyInfo pi in properties)
            {
                var ouput = pi.GetValue(obj);
                //if the ouput type has overridden the ToString method, use that
                if (ouput != null && ouput.GetType().GetMethods().Where(gm => gm.Name == "ToString" && gm.DeclaringType != typeof(object)).Count() > 0)
                {
                    output += pi.Name + " = " + ouput.ToString() + ", ";
                }
                else
                    output += pi.Name + " = " + pi.GetValue(obj)?.ToMeaningfulString(depth + 1) + ", ";
            }
            if (depth == 0)
            {
                output = output.Substring(0, output.Length - 2);
                output += "}";
            }
            return output;
        }
    }
}
