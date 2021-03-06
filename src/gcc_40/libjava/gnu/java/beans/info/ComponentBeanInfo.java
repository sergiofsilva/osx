/* gnu.java.beans.info.ComponentBeanInfo
   Copyright (C) 1998 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
 
GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


package gnu.java.beans.info;

import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;
import java.beans.SimpleBeanInfo;

/** BeanInfo class for java.awt.Component.
 ** This provides a few properties, but that's
 ** it.
 ** @author John Keiser
 ** @version 1.1.0, Aug 1 1998
 **/
public class ComponentBeanInfo extends SimpleBeanInfo {
	static PropertyDescriptor[] properties;
	static {
		try {
		properties = new PropertyDescriptor[6];
		properties[0] = new PropertyDescriptor("name",java.awt.Component.class);
		properties[1] = new PropertyDescriptor("background",java.awt.Component.class);
		properties[2] = new PropertyDescriptor("foreground",java.awt.Component.class);
		properties[3] = new PropertyDescriptor("font",java.awt.Component.class);
		properties[4] = new PropertyDescriptor("enabled",java.awt.Component.class);
		properties[5] = new PropertyDescriptor("visible",java.awt.Component.class);
		} catch(IntrospectionException E) {
			properties = null;
			throw new UnknownError("Could not introspect some java.awt.Component properties.");
		}
	}
	public ComponentBeanInfo() {
		super();
	}

	public PropertyDescriptor[] getPropertyDescriptors() {
		return properties;
	}
}

