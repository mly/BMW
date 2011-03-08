class CreateVelocityEvents < ActiveRecord::Migration
  def self.up
    create_table :velocity_events do |t|
      t.decimal :latitude
      t.decimal :longitude
      t.decimal :velocity
      t.decimal :heading
      t.timestamp :time
      t.string :device_id

      t.timestamps
    end
  end

  def self.down
    drop_table :velocity_events
  end
end
