require 'test_helper'

class VelocityEventsControllerTest < ActionController::TestCase
  setup do
    @velocity_event = velocity_events(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:velocity_events)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create velocity_event" do
    assert_difference('VelocityEvent.count') do
      post :create, :velocity_event => @velocity_event.attributes
    end

    assert_redirected_to velocity_event_path(assigns(:velocity_event))
  end

  test "should show velocity_event" do
    get :show, :id => @velocity_event.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @velocity_event.to_param
    assert_response :success
  end

  test "should update velocity_event" do
    put :update, :id => @velocity_event.to_param, :velocity_event => @velocity_event.attributes
    assert_redirected_to velocity_event_path(assigns(:velocity_event))
  end

  test "should destroy velocity_event" do
    assert_difference('VelocityEvent.count', -1) do
      delete :destroy, :id => @velocity_event.to_param
    end

    assert_redirected_to velocity_events_path
  end
end
