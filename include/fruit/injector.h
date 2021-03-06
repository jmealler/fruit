/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRUIT_INJECTOR_H
#define FRUIT_INJECTOR_H

#include "component.h"
#include "provider.h"

namespace fruit {

template <typename... P>
class Injector : public Provider<P...> {
private:
  using Super = Provider<P...>;
  
public:
  Injector() = delete;
  
  ~Injector();
  
  // Copying an Injector is forbidden.
  Injector(const Injector&) = delete;
  
  // Moving an Injector is allowed.
  Injector(Injector&&) = default;
  
  /**
   * Creation of an injector from a component.
   * 
   * Example usage:
   * 
   * Injector<Foo, Bar> injector(getFooBarComponent());
   * Foo* foo(injector); // Equivalent to: Foo* foo = injector.get<Foo*>();
   */
  Injector(const Component<P...>& component);
  Injector(Component<P...>&& component);
  
  /**
   * Gets all multibindings for a type T.
   * 
   * Note that multibindings are independent from bindings, so the binding for T (if any) is not returned.
   * This returns an empty set if there are no multibindings.
   */
  template <typename T>
  std::set<T*> getMultibindings();
  
  /**
   * Eagerly injects all reachable bindings and multibindings of this injector.
   * Unreachable bindings (i.e. bindings that will never be used anyway) are not processed.
   * Call this if the injector will be shared by multiple threads (directly or through per-thread Providers).
   */
  void eagerlyInjectAll();
};

} // namespace fruit


#endif // FRUIT_INJECTOR_H
